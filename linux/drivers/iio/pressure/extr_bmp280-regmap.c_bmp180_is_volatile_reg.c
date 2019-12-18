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
#define  BMP180_REG_OUT_LSB 131 
#define  BMP180_REG_OUT_MSB 130 
#define  BMP180_REG_OUT_XLSB 129 
#define  BMP280_REG_CTRL_MEAS 128 

__attribute__((used)) static bool bmp180_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case BMP180_REG_OUT_XLSB:
	case BMP180_REG_OUT_LSB:
	case BMP180_REG_OUT_MSB:
	case BMP280_REG_CTRL_MEAS:
		return true;
	default:
		return false;
	}
}