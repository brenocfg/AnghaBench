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
#define  BMP280_REG_CONFIG 131 
#define  BMP280_REG_CTRL_HUMIDITY 130 
#define  BMP280_REG_CTRL_MEAS 129 
#define  BMP280_REG_RESET 128 

__attribute__((used)) static bool bmp280_is_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case BMP280_REG_CONFIG:
	case BMP280_REG_CTRL_HUMIDITY:
	case BMP280_REG_CTRL_MEAS:
	case BMP280_REG_RESET:
		return true;
	default:
		return false;
	};
}