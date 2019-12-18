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
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_PULL_DOWN 131 
#define  PIN_CONFIG_BIAS_PULL_UP 130 
#define  PIN_CONFIG_DRIVE_STRENGTH 129 
#define  PIN_CONFIG_INPUT_ENABLE 128 
 unsigned long pinconf_to_config_packed (int,int /*<<< orphan*/ ) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int uniphier_conf_pin_bias_get (struct pinctrl_dev*,unsigned int,int) ; 
 int uniphier_conf_pin_drive_get (struct pinctrl_dev*,unsigned int,int /*<<< orphan*/ *) ; 
 int uniphier_conf_pin_input_enable_get (struct pinctrl_dev*,unsigned int) ; 

__attribute__((used)) static int uniphier_conf_pin_config_get(struct pinctrl_dev *pctldev,
					unsigned pin,
					unsigned long *configs)
{
	enum pin_config_param param = pinconf_to_config_param(*configs);
	bool has_arg = false;
	u32 arg;
	int ret;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
		ret = uniphier_conf_pin_bias_get(pctldev, pin, param);
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		ret = uniphier_conf_pin_drive_get(pctldev, pin, &arg);
		has_arg = true;
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		ret = uniphier_conf_pin_input_enable_get(pctldev, pin);
		break;
	default:
		/* unsupported parameter */
		ret = -EINVAL;
		break;
	}

	if (ret == 0 && has_arg)
		*configs = pinconf_to_config_packed(param, arg);

	return ret;
}