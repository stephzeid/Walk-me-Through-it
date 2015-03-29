#include <Stepper.h>

#define trigPin 13 //Sensor 1
#define echoPin 12 // Sensor 1
#define trigPin1 10 //Sensor 2
#define echoPin1 11 // Sensor 2

int ledPin1 = 4;// use the built in LED on pin 13 of the Uno
int ledPin2 = 5;
int turnDirection = 0;
int flag = 0;        // make sure that you return the state only once
int space = 20; //space determines distance at which objects are considered dangerous

void setup() {
    // sets the pins as outputs:
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    //digitalWrite(ledPin, LOW);
   // Set up pins for ultrasonic
    
    Serial.begin(9600); // Default connection rate for my BT module
    Serial.println("Hello Alexandra, this is your Arduino!");
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    
}

void loop() {
  long duration, distance, duration1, distance1;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.1;
  
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");
  
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2)/29.1;
  
  //Serial.print("Distance: ");
  //Serial.print(distance1);
  //Serial.println(" cm");
  
  flag=0;
  
    //if some data is sent via bluetooth, read it and save it in the turnDirection variable
   if(Serial.available() > 0)
   {
     turnDirection = Serial.read();
     
   }

   
   //if the distance from either sensor is less than the space allowed
    if (distance < space || distance1 < space) 
    {
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        
          //Serial.println("If left sensor or right sensor is activated, left motor and right motor will run");
        
    }
    
    //if the app sends a left turn
    else if(turnDirection == '1')
    {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
     delay(1000);
          //Serial.println("If a left turn is required, the left motor will run");
        
      
    }
    
    //if the app sends a right turn
    else if(turnDirection == '2')
    {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      delay(1000);
      
     
          //Serial.println("If a right turn is required, the right motor will run");
    }
     
    //if no turn is sent, and no objects are within space
    else
    {
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
    
          //Serial.println("Do not do anything if nothing is sensed and no turns are required");
 
    }
    
    turnDirection = 0;
}
