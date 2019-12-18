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
typedef  int uint8_t ;

/* Variables and functions */
#define  SMU7_I2CLineID_DDC1 135 
#define  SMU7_I2CLineID_DDC2 134 
#define  SMU7_I2CLineID_DDC3 133 
#define  SMU7_I2CLineID_DDC4 132 
#define  SMU7_I2CLineID_DDC5 131 
#define  SMU7_I2CLineID_DDC6 130 
#define  SMU7_I2CLineID_DDCVGA 129 
#define  SMU7_I2CLineID_SCLSDA 128 
 int SMU7_I2C_DDC1CLK ; 
 int SMU7_I2C_DDC1DATA ; 
 int SMU7_I2C_DDC2CLK ; 
 int SMU7_I2C_DDC2DATA ; 
 int SMU7_I2C_DDC3CLK ; 
 int SMU7_I2C_DDC3DATA ; 
 int SMU7_I2C_DDC4CLK ; 
 int SMU7_I2C_DDC4DATA ; 
 int SMU7_I2C_DDC5CLK ; 
 int SMU7_I2C_DDC5DATA ; 
 int SMU7_I2C_DDC6CLK ; 
 int SMU7_I2C_DDC6DATA ; 
 int SMU7_I2C_DDCVGACLK ; 
 int SMU7_I2C_DDCVGADATA ; 
 int SMU7_I2C_SCL ; 
 int SMU7_I2C_SDA ; 

__attribute__((used)) static void get_scl_sda_value(uint8_t line, uint8_t *scl, uint8_t *sda)
{
	switch (line) {
	case SMU7_I2CLineID_DDC1:
		*scl = SMU7_I2C_DDC1CLK;
		*sda = SMU7_I2C_DDC1DATA;
		break;
	case SMU7_I2CLineID_DDC2:
		*scl = SMU7_I2C_DDC2CLK;
		*sda = SMU7_I2C_DDC2DATA;
		break;
	case SMU7_I2CLineID_DDC3:
		*scl = SMU7_I2C_DDC3CLK;
		*sda = SMU7_I2C_DDC3DATA;
		break;
	case SMU7_I2CLineID_DDC4:
		*scl = SMU7_I2C_DDC4CLK;
		*sda = SMU7_I2C_DDC4DATA;
		break;
	case SMU7_I2CLineID_DDC5:
		*scl = SMU7_I2C_DDC5CLK;
		*sda = SMU7_I2C_DDC5DATA;
		break;
	case SMU7_I2CLineID_DDC6:
		*scl = SMU7_I2C_DDC6CLK;
		*sda = SMU7_I2C_DDC6DATA;
		break;
	case SMU7_I2CLineID_SCLSDA:
		*scl = SMU7_I2C_SCL;
		*sda = SMU7_I2C_SDA;
		break;
	case SMU7_I2CLineID_DDCVGA:
		*scl = SMU7_I2C_DDCVGACLK;
		*sda = SMU7_I2C_DDCVGADATA;
		break;
	default:
		*scl = 0;
		*sda = 0;
		break;
	}
}