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
typedef  int /*<<< orphan*/  u16 ;
struct pinctrl_dev {int dummy; } ;
struct iproc_gpio {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_STRENGTH 128 
 int /*<<< orphan*/  iproc_gpio_get_pull (struct iproc_gpio*,unsigned int,int*,int*) ; 
 int iproc_gpio_get_strength (struct iproc_gpio*,unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int iproc_pin_to_gpio (unsigned int) ; 
 scalar_t__ iproc_pinconf_param_is_disabled (struct iproc_gpio*,int) ; 
 unsigned long pinconf_to_config_packed (int,int /*<<< orphan*/ ) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct iproc_gpio* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int iproc_pin_config_get(struct pinctrl_dev *pctldev, unsigned pin,
				 unsigned long *config)
{
	struct iproc_gpio *chip = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	unsigned gpio = iproc_pin_to_gpio(pin);
	u16 arg;
	bool disable, pull_up;
	int ret;

	if (iproc_pinconf_param_is_disabled(chip, param))
		return -ENOTSUPP;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		iproc_gpio_get_pull(chip, gpio, &disable, &pull_up);
		if (disable)
			return 0;
		else
			return -EINVAL;

	case PIN_CONFIG_BIAS_PULL_UP:
		iproc_gpio_get_pull(chip, gpio, &disable, &pull_up);
		if (!disable && pull_up)
			return 0;
		else
			return -EINVAL;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		iproc_gpio_get_pull(chip, gpio, &disable, &pull_up);
		if (!disable && !pull_up)
			return 0;
		else
			return -EINVAL;

	case PIN_CONFIG_DRIVE_STRENGTH:
		ret = iproc_gpio_get_strength(chip, gpio, &arg);
		if (ret)
			return ret;
		*config = pinconf_to_config_packed(param, arg);

		return 0;

	default:
		return -ENOTSUPP;
	}

	return -ENOTSUPP;
}