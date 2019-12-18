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
struct stm32_pinctrl {int /*<<< orphan*/  dev; } ;
struct stm32_gpio_bank {int dummy; } ;
struct pinctrl_gpio_range {int /*<<< orphan*/  gc; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 134 
#define  PIN_CONFIG_BIAS_PULL_DOWN 133 
#define  PIN_CONFIG_BIAS_PULL_UP 132 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 131 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 130 
#define  PIN_CONFIG_OUTPUT 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int /*<<< orphan*/  __stm32_gpio_set (struct stm32_gpio_bank*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct stm32_gpio_bank* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 struct stm32_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin (struct pinctrl_dev*,unsigned int) ; 
 int stm32_gpio_pin (unsigned int) ; 
 int stm32_pconf_set_bias (struct stm32_gpio_bank*,int,int) ; 
 int stm32_pconf_set_driving (struct stm32_gpio_bank*,int,int) ; 
 int stm32_pconf_set_speed (struct stm32_gpio_bank*,int,int) ; 
 int stm32_pmx_gpio_set_direction (struct pinctrl_dev*,struct pinctrl_gpio_range*,unsigned int,int) ; 

__attribute__((used)) static int stm32_pconf_parse_conf(struct pinctrl_dev *pctldev,
		unsigned int pin, enum pin_config_param param,
		enum pin_config_param arg)
{
	struct stm32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct pinctrl_gpio_range *range;
	struct stm32_gpio_bank *bank;
	int offset, ret = 0;

	range = pinctrl_find_gpio_range_from_pin(pctldev, pin);
	if (!range) {
		dev_err(pctl->dev, "No gpio range defined.\n");
		return -EINVAL;
	}

	bank = gpiochip_get_data(range->gc);
	offset = stm32_gpio_pin(pin);

	switch (param) {
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		ret = stm32_pconf_set_driving(bank, offset, 0);
		break;
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		ret = stm32_pconf_set_driving(bank, offset, 1);
		break;
	case PIN_CONFIG_SLEW_RATE:
		ret = stm32_pconf_set_speed(bank, offset, arg);
		break;
	case PIN_CONFIG_BIAS_DISABLE:
		ret = stm32_pconf_set_bias(bank, offset, 0);
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		ret = stm32_pconf_set_bias(bank, offset, 1);
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		ret = stm32_pconf_set_bias(bank, offset, 2);
		break;
	case PIN_CONFIG_OUTPUT:
		__stm32_gpio_set(bank, offset, arg);
		ret = stm32_pmx_gpio_set_direction(pctldev, range, pin, false);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}