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
typedef  int u32 ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int LPC18XX_SCU_USB1_EPD ; 
 int LPC18XX_SCU_USB1_EPWR ; 
#define  PIN_CONFIG_BIAS_DISABLE 130 
#define  PIN_CONFIG_BIAS_PULL_DOWN 129 
#define  PIN_CONFIG_LOW_POWER_MODE 128 

__attribute__((used)) static int lpc18xx_pconf_get_usb1(enum pin_config_param param, int *arg, u32 reg)
{
	switch (param) {
	case PIN_CONFIG_LOW_POWER_MODE:
		if (reg & LPC18XX_SCU_USB1_EPWR)
			*arg = 0;
		else
			*arg = 1;
		break;

	case PIN_CONFIG_BIAS_DISABLE:
		if (reg & LPC18XX_SCU_USB1_EPD)
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (reg & LPC18XX_SCU_USB1_EPD)
			*arg = 1;
		else
			return -EINVAL;
		break;

	default:
		return -ENOTSUPP;
	}

	return 0;
}