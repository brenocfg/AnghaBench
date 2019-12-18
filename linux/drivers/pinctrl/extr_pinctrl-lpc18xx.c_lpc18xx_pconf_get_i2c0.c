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
typedef  int u8 ;
typedef  int u32 ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int LPC18XX_SCU_I2C0_EFP ; 
 int LPC18XX_SCU_I2C0_EHD ; 
 int LPC18XX_SCU_I2C0_EZI ; 
 int LPC18XX_SCU_I2C0_SCL_SHIFT ; 
 int LPC18XX_SCU_I2C0_SDA_SHIFT ; 
 int LPC18XX_SCU_I2C0_ZIF ; 
#define  PIN_CONFIG_INPUT_ENABLE 131 
#define  PIN_CONFIG_INPUT_SCHMITT 130 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 unsigned int PIN_I2C0_SCL ; 

__attribute__((used)) static int lpc18xx_pconf_get_i2c0(enum pin_config_param param, int *arg, u32 reg,
				  unsigned pin)
{
	u8 shift;

	if (pin == PIN_I2C0_SCL)
		shift = LPC18XX_SCU_I2C0_SCL_SHIFT;
	else
		shift = LPC18XX_SCU_I2C0_SDA_SHIFT;

	switch (param) {
	case PIN_CONFIG_INPUT_ENABLE:
		if (reg & (LPC18XX_SCU_I2C0_EZI << shift))
			*arg = 1;
		else
			return -EINVAL;
		break;

	case PIN_CONFIG_SLEW_RATE:
		if (reg & (LPC18XX_SCU_I2C0_EHD << shift))
			*arg = 1;
		else
			*arg = 0;
		break;

	case PIN_CONFIG_INPUT_SCHMITT:
		if (reg & (LPC18XX_SCU_I2C0_EFP << shift))
			*arg = 3;
		else
			*arg = 50;
		break;

	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		if (reg & (LPC18XX_SCU_I2C0_ZIF << shift))
			return -EINVAL;
		else
			*arg = 1;
		break;

	default:
		return -ENOTSUPP;
	}

	return 0;
}