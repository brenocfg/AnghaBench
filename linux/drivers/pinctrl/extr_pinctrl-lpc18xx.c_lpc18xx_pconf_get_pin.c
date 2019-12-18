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
struct pinctrl_dev {int dummy; } ;
struct lpc18xx_pin_caps {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int LPC18XX_SCU_PIN_EHD_MASK ; 
 int LPC18XX_SCU_PIN_EHD_POS ; 
 int LPC18XX_SCU_PIN_EHS ; 
 int LPC18XX_SCU_PIN_EPD ; 
 int LPC18XX_SCU_PIN_EPUN ; 
 int LPC18XX_SCU_PIN_EZI ; 
 int LPC18XX_SCU_PIN_ZIF ; 
#define  PIN_CONFIG_BIAS_DISABLE 135 
#define  PIN_CONFIG_BIAS_PULL_DOWN 134 
#define  PIN_CONFIG_BIAS_PULL_UP 133 
#define  PIN_CONFIG_DRIVE_STRENGTH 132 
#define  PIN_CONFIG_GPIO_PIN_INT 131 
#define  PIN_CONFIG_INPUT_ENABLE 130 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int /*<<< orphan*/  TYPE_HD ; 
 int lpc18xx_pconf_get_gpio_pin_int (struct pinctrl_dev*,int*,unsigned int) ; 

__attribute__((used)) static int lpc18xx_pconf_get_pin(struct pinctrl_dev *pctldev, unsigned param,
				 int *arg, u32 reg, unsigned pin,
				 struct lpc18xx_pin_caps *pin_cap)
{
	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if ((!(reg & LPC18XX_SCU_PIN_EPD)) && (reg & LPC18XX_SCU_PIN_EPUN))
			;
		else
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		if (reg & LPC18XX_SCU_PIN_EPUN)
			return -EINVAL;
		else
			*arg = 1;
		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (reg & LPC18XX_SCU_PIN_EPD)
			*arg = 1;
		else
			return -EINVAL;
		break;

	case PIN_CONFIG_INPUT_ENABLE:
		if (reg & LPC18XX_SCU_PIN_EZI)
			*arg = 1;
		else
			return -EINVAL;
		break;

	case PIN_CONFIG_SLEW_RATE:
		if (pin_cap->type == TYPE_HD)
			return -ENOTSUPP;

		if (reg & LPC18XX_SCU_PIN_EHS)
			*arg = 1;
		else
			*arg = 0;
		break;

	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		if (reg & LPC18XX_SCU_PIN_ZIF)
			return -EINVAL;
		else
			*arg = 1;
		break;

	case PIN_CONFIG_DRIVE_STRENGTH:
		if (pin_cap->type != TYPE_HD)
			return -ENOTSUPP;

		*arg = (reg & LPC18XX_SCU_PIN_EHD_MASK) >> LPC18XX_SCU_PIN_EHD_POS;
		switch (*arg) {
		case 3: *arg += 5;
			/* fall through */
		case 2: *arg += 5;
			/* fall through */
		case 1: *arg += 3;
			/* fall through */
		case 0: *arg += 4;
		}
		break;

	case PIN_CONFIG_GPIO_PIN_INT:
		return lpc18xx_pconf_get_gpio_pin_int(pctldev, arg, pin);

	default:
		return -ENOTSUPP;
	}

	return 0;
}