//esp32 board version must be 2.0.11
//otherwise the code will not compile

#include "BluetoothSerial.h"
#include <Arduino.h>
#include <NewPing.h>
BluetoothSerial serialBT;

//Bluetooth signal Store in this variable
char btSignal;

//initial Speed
int Speed = 100;

//declare channel for pwm Output
#define R 0
#define L 1

//PWM Pin for Controlling the speed
int enA = 5;
int enB = 23;

//motor controlling pin
int IN1 = 12;
int IN2 = 13;
int IN3 = 26;
int IN4 = 27;


#define TRIG_PIN 33
#define ECHO_PIN 32
#define MAX_DISTANCE 200

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);


void setup() {
  Serial.begin(115200);

  //Bluetooth Name
  serialBT.begin("scar");

  //output pin declare
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Intial State of Car
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  unsigned int dis= sonar.ping_cm();
  delay(20);

  while (serialBT.available()) {
    btSignal = serialBT.read();
    

    Serial.println(btSignal);
    Serial.println(dis);

    if (btSignal == '0') Speed = 100;
    if (btSignal == '1') Speed = 110;
    if (btSignal == '2') Speed = 120;
    if (btSignal == '3') Speed = 130;
    if (btSignal == '4') Speed = 140;
    if (btSignal == '5') Speed = 150;
    if (btSignal == '6') Speed = 180;
    if (btSignal == '7') Speed = 200;
    if (btSignal == '8') Speed = 220;
    if (btSignal == '9') Speed = 240;
    if (btSignal == 'q') Speed = 255;

//to see the incoming signal in serial monitor
    Serial.println(btSignal);
    Serial.println(dis);
    
    
  //backwar   
    if (btSignal == 'B') {
      backward();
    }

  //forward
    else if (btSignal == 'F') {
       if(dis==0 || dis>20  ){
      forward();
       }
       else
       {
        stop();
       }
    }

  //LEFT
    else if (btSignal == 'L') {
      left();
    }

  //RIGHT
    else if (btSignal == 'R') {
      right();
    }

  //STOP
    else if (btSignal == 'S') {
      stop();
    }

}
}

//function for control motor
void backward() {


  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  }

void forward() {
 

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {


  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
 

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop() {


    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
