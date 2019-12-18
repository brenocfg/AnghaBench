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
typedef  int /*<<< orphan*/  u32 ;
struct stmfx_pinctrl {int /*<<< orphan*/  gpio_chip; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 134 
#define  PIN_CONFIG_BIAS_PULL_DOWN 133 
#define  PIN_CONFIG_BIAS_PULL_PIN_DEFAULT 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 130 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 129 
#define  PIN_CONFIG_OUTPUT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct stmfx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin_nolock (struct pinctrl_dev*,unsigned int) ; 
 int stmfx_gpio_direction_output (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int stmfx_gpio_get_direction (int /*<<< orphan*/ *,unsigned int) ; 
 int stmfx_pinconf_set_pupd (struct stmfx_pinctrl*,unsigned int,int) ; 
 int stmfx_pinconf_set_type (struct stmfx_pinctrl*,unsigned int,int) ; 

__attribute__((used)) static int stmfx_pinconf_set(struct pinctrl_dev *pctldev, unsigned int pin,
			     unsigned long *configs, unsigned int num_configs)
{
	struct stmfx_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct pinctrl_gpio_range *range;
	enum pin_config_param param;
	u32 arg;
	int dir, i, ret;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	if (!range) {
		dev_err(pctldev->dev, "pin %d is not available\n", pin);
		return -EINVAL;
	}

	dir = stmfx_gpio_get_direction(&pctl->gpio_chip, pin);
	if (dir < 0)
		return dir;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
		case PIN_CONFIG_BIAS_DISABLE:
		case PIN_CONFIG_DRIVE_PUSH_PULL:
			ret = stmfx_pinconf_set_type(pctl, pin, 0);
			if (ret)
				return ret;
			break;
		case PIN_CONFIG_BIAS_PULL_DOWN:
			ret = stmfx_pinconf_set_type(pctl, pin, 1);
			if (ret)
				return ret;
			ret = stmfx_pinconf_set_pupd(pctl, pin, 0);
			if (ret)
				return ret;
			break;
		case PIN_CONFIG_BIAS_PULL_UP:
			ret = stmfx_pinconf_set_type(pctl, pin, 1);
			if (ret)
				return ret;
			ret = stmfx_pinconf_set_pupd(pctl, pin, 1);
			if (ret)
				return ret;
			break;
		case PIN_CONFIG_DRIVE_OPEN_DRAIN:
			ret = stmfx_pinconf_set_type(pctl, pin, 1);
			if (ret)
				return ret;
			break;
		case PIN_CONFIG_OUTPUT:
			ret = stmfx_gpio_direction_output(&pctl->gpio_chip,
							  pin, arg);
			if (ret)
				return ret;
			break;
		default:
			return -ENOTSUPP;
		}
	}

	return 0;
}