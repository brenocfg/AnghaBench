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
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct lpc18xx_pin_caps {int /*<<< orphan*/  type; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int lpc18xx_pconf_set_gpio_pin_int (struct pinctrl_dev*,int,unsigned int) ; 

__attribute__((used)) static int lpc18xx_pconf_set_pin(struct pinctrl_dev *pctldev, unsigned param,
				 u32 param_val, u32 *reg, unsigned pin,
				 struct lpc18xx_pin_caps *pin_cap)
{
	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		*reg &= ~LPC18XX_SCU_PIN_EPD;
		*reg |= LPC18XX_SCU_PIN_EPUN;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		*reg &= ~LPC18XX_SCU_PIN_EPUN;
		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		*reg |= LPC18XX_SCU_PIN_EPD;
		break;

	case PIN_CONFIG_INPUT_ENABLE:
		if (param_val)
			*reg |= LPC18XX_SCU_PIN_EZI;
		else
			*reg &= ~LPC18XX_SCU_PIN_EZI;
		break;

	case PIN_CONFIG_SLEW_RATE:
		if (pin_cap->type == TYPE_HD) {
			dev_err(pctldev->dev, "Slew rate unsupported on high-drive pins\n");
			return -ENOTSUPP;
		}

		if (param_val == 0)
			*reg &= ~LPC18XX_SCU_PIN_EHS;
		else
			*reg |= LPC18XX_SCU_PIN_EHS;
		break;

	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		if (param_val)
			*reg &= ~LPC18XX_SCU_PIN_ZIF;
		else
			*reg |= LPC18XX_SCU_PIN_ZIF;
		break;

	case PIN_CONFIG_DRIVE_STRENGTH:
		if (pin_cap->type != TYPE_HD) {
			dev_err(pctldev->dev, "Drive strength available only on high-drive pins\n");
			return -ENOTSUPP;
		}
		*reg &= ~LPC18XX_SCU_PIN_EHD_MASK;

		switch (param_val) {
		case 20: param_val -= 5;
			 /* fall through */
		case 14: param_val -= 5;
			 /* fall through */
		case  8: param_val -= 3;
			 /* fall through */
		case  4: param_val -= 4;
			 break;
		default:
			dev_err(pctldev->dev, "Drive strength %u unsupported\n", param_val);
			return -ENOTSUPP;
		}
		*reg |= param_val << LPC18XX_SCU_PIN_EHD_POS;
		break;

	case PIN_CONFIG_GPIO_PIN_INT:
		return lpc18xx_pconf_set_gpio_pin_int(pctldev, param_val, pin);

	default:
		dev_err(pctldev->dev, "Property not supported\n");
		return -ENOTSUPP;
	}

	return 0;
}