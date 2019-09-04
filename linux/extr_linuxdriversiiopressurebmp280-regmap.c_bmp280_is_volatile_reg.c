#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int dummy; } ;

/* Variables and functions */
#define  BMP280_REG_HUMIDITY_LSB 136 
#define  BMP280_REG_HUMIDITY_MSB 135 
#define  BMP280_REG_PRESS_LSB 134 
#define  BMP280_REG_PRESS_MSB 133 
#define  BMP280_REG_PRESS_XLSB 132 
#define  BMP280_REG_STATUS 131 
#define  BMP280_REG_TEMP_LSB 130 
#define  BMP280_REG_TEMP_MSB 129 
#define  BMP280_REG_TEMP_XLSB 128 

__attribute__((used)) static bool bmp280_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case BMP280_REG_HUMIDITY_LSB:
	case BMP280_REG_HUMIDITY_MSB:
	case BMP280_REG_TEMP_XLSB:
	case BMP280_REG_TEMP_LSB:
	case BMP280_REG_TEMP_MSB:
	case BMP280_REG_PRESS_XLSB:
	case BMP280_REG_PRESS_LSB:
	case BMP280_REG_PRESS_MSB:
	case BMP280_REG_STATUS:
		return true;
	default:
		return false;
	}
}