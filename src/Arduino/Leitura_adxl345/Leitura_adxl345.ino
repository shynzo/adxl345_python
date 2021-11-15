/* 
* Código retirado e adaptado de: https://github.com/shynzo/mpu6050_python/blob/main/src/Arduino/Leitura_mpu6050/Leitura_mpu6050.ino
* Criado por: shynzo
*
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

int configg = 0;
char command;

void setup(void) {
  Serial.begin(115200);
  // Tentando inicializar
  while (!accel.begin()) {
    Serial.println("Falha ao encontrar ADXL345 chip");
    delay(10);
    if (accel.begin()) {
      break;
    }
  } //Enquanto não conseguir encontrar o chip MPU6050, irá ficar neste loop
  Serial.println("ADXL345 Encontrado!");
  Wire.begin(); //Inicializando leitura
  while (1) { //Neste loop, fica ao aguardo da configuração da escala do acelerômetro
    if (Serial.available()) {
      Serial.println(configg);
      command = Serial.read(); //Lê o comando Serial advindo do Python
      if (command == '0') {
        accel.setRange(ADXL345_RANGE_2_G); //Setta para +-2g
        break;
      }
      else if (command == '1') {
        accel.setRange(ADXL345_RANGE_4_G); //Setta para +-4g
        break;
      }
      else if (command == '2') {
        accel.setRange(ADXL345_RANGE_8_G); //Setta para +-8g
        break;
      }
      else if (command == '3') {
        accel.setRange(ADXL345_RANGE_16_G); //Setta para +-16g
        break;
      }
      else {
        continue;
      }
    }
  }
}

void loop(void)
{
  sensors_event_t a; // captura os eventos do sensor
  accel.getEvent(&a);
  Serial.println((String)a.acceleration.x + ";" + (String)a.acceleration.y + ";" + (String)a.acceleration.z);
  /* Display the results (acceleration is measured in m/s^2)
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  "); Serial.println("m/s^2 ");
  */
  delay(500);
}
