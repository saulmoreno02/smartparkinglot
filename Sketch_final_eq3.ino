// C++ code
//
#include <Servo.h>

int Espacio1 = 0;

int Espacio2 = 0;

int Puerta = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_4;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, INPUT);
  servo_4.attach(4, 500, 2500);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}

void loop()
{
  if (0.01723 * readUltrasonicDistance(13, 12) < 5) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    Espacio1 = 1;
  } else {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    Espacio1 = 0;
  }
  if (0.01723 * readUltrasonicDistance(11, 10) < 5) {
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    Espacio2 = 1;
  } else {
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    Espacio2 = 0;
  }
  Puerta = (Espacio1 + Espacio2);
  if (Puerta < 2) {
    digitalWrite(5, HIGH);
    digitalWrite(9, LOW);
  } else {
    digitalWrite(5, LOW);
    digitalWrite(9, HIGH);
  }
  if (Puerta < 2 && digitalRead(8) == HIGH) {
    servo_4.write(90);
    delay(5000); // Wait for 5000 millisecond(s)
  } else {
    servo_4.write(0);
  }
  delay(500); // Wait for 500 millisecond(s)
}