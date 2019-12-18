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
struct stmfx_pinctrl {int /*<<< orphan*/  gpio_chip; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 133 
#define  PIN_CONFIG_BIAS_PULL_DOWN 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 130 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 129 
#define  PIN_CONFIG_OUTPUT 128 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct stmfx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin_nolock (struct pinctrl_dev*,unsigned int) ; 
 int stmfx_gpio_get (int /*<<< orphan*/ *,unsigned int) ; 
 int stmfx_gpio_get_direction (int /*<<< orphan*/ *,unsigned int) ; 
 int stmfx_pinconf_get_pupd (struct stmfx_pinctrl*,unsigned int) ; 
 int stmfx_pinconf_get_type (struct stmfx_pinctrl*,unsigned int) ; 

__attribute__((used)) static int stmfx_pinconf_get(struct pinctrl_dev *pctldev,
			     unsigned int pin, unsigned long *config)
{
	struct stmfx_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	u32 param = pinconf_to_config_param(*config);
	struct pinctrl_gpio_range *range;
	u32 arg = 0;
	int ret, dir, type, pupd;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	if (!range)
		return -EINVAL;

	dir = stmfx_gpio_get_direction(&pctl->gpio_chip, pin);
	if (dir < 0)
		return dir;
	type = stmfx_pinconf_get_type(pctl, pin);
	if (type < 0)
		return type;
	pupd = stmfx_pinconf_get_pupd(pctl, pin);
	if (pupd < 0)
		return pupd;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if ((!dir && (!type || !pupd)) || (dir && !type))
			arg = 1;
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (dir && type && !pupd)
			arg = 1;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		if (type && pupd)
			arg = 1;
		break;
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		if ((!dir && type) || (dir && !type))
			arg = 1;
		break;
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		if ((!dir && !type) || (dir && type))
			arg = 1;
		break;
	case PIN_CONFIG_OUTPUT:
		if (dir)
			return -EINVAL;

		ret = stmfx_gpio_get(&pctl->gpio_chip, pin);
		if (ret < 0)
			return ret;

		arg = ret;
		break;
	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}