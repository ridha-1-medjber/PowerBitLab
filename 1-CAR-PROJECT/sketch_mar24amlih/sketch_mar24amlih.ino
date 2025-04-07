#include <WiFi.h>
#include <WebServer.h>

// Replace with your WiFi credentials
const char* ssid = "REDA";
const char* password = "Medjber123123";

// Define motor control pins
#define MOTOR1_PIN1 12
#define MOTOR1_PIN2 13 
#define MOTOR2_PIN1 14
#define MOTOR2_PIN2 15

WebServer server(80);

void setup() {
    delay(1000);  // Allow power to stabilize (fixes boot issue)
    Serial.begin(115200);
    Serial.println("Booting ESP32-CAM...");

    // Set motor pins as output
    pinMode(MOTOR1_PIN1, OUTPUT);
    pinMode(MOTOR1_PIN2, OUTPUT);
    pinMode(MOTOR2_PIN1, OUTPUT);
    pinMode(MOTOR2_PIN2, OUTPUT);
    
    Serial.println("WiFi Connecting...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi Connected!");
    Serial.print("ESP32-CAM IP Address: ");
    Serial.println(WiFi.localIP());

    // Define HTTP endpoints
    server.on("/", []() {
        server.send(200, "text/html", "<h1>ESP32-CAM Car Control</h1><p>Use /forward, /backward, /left, /right, /stop</p>");
    });

    server.on("/forward", []() {
        moveForward();
        server.send(200, "text/plain", "Moving Forward");
    });

    server.on("/backward", []() {
        moveBackward();
        server.send(200, "text/plain", "Moving Backward");
    });

    server.on("/left", []() {
        turnLeft();
        server.send(200, "text/plain", "Turning Left");
    });

    server.on("/right", []() {
        turnRight();
        server.send(200, "text/plain", "Turning Right");
    });

    server.on("/stop", []() {
        stopMotors();
        server.send(200, "text/plain", "Stopped");
    });

    server.begin();
}

void loop() {
    server.handleClient();
}

// Motor control functions
void moveForward() {
    Serial.println("Received: Forward");
    digitalWrite(MOTOR1_PIN1, HIGH);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, HIGH);
    digitalWrite(MOTOR2_PIN2, LOW);
}

void moveBackward() {
    Serial.println("Received: Backward");
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, HIGH);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, HIGH);
}

void turnLeft() {
    Serial.println("Received: left");
    digitalWrite(MOTOR1_PIN1, HIGH);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, HIGH);
          delay(1000); 
      digitalWrite(MOTOR1_PIN1, HIGH);
      digitalWrite(MOTOR1_PIN2, LOW);
      digitalWrite(MOTOR2_PIN1, HIGH);
      digitalWrite(MOTOR2_PIN2, LOW);
}

void turnRight() {
    Serial.println("Received: right");
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, HIGH);
    digitalWrite(MOTOR2_PIN1, HIGH);
    digitalWrite(MOTOR2_PIN2, LOW);
         delay(1000);  
      digitalWrite(MOTOR1_PIN1, HIGH);
      digitalWrite(MOTOR1_PIN2, LOW);
      digitalWrite(MOTOR2_PIN1, HIGH);
      digitalWrite(MOTOR2_PIN2, LOW);
}

void stopMotors() {
    Serial.println("Received: Stop");
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, LOW);
}




