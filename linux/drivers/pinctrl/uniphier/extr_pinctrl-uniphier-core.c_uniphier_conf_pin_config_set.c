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
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 133 
#define  PIN_CONFIG_BIAS_PULL_DOWN 132 
#define  PIN_CONFIG_BIAS_PULL_PIN_DEFAULT 131 
#define  PIN_CONFIG_BIAS_PULL_UP 130 
#define  PIN_CONFIG_DRIVE_STRENGTH 129 
#define  PIN_CONFIG_INPUT_ENABLE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int uniphier_conf_pin_bias_set (struct pinctrl_dev*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int uniphier_conf_pin_drive_set (struct pinctrl_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int uniphier_conf_pin_input_enable (struct pinctrl_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_conf_pin_config_set(struct pinctrl_dev *pctldev,
					unsigned pin,
					unsigned long *configs,
					unsigned num_configs)
{
	int i, ret;

	for (i = 0; i < num_configs; i++) {
		enum pin_config_param param =
					pinconf_to_config_param(configs[i]);
		u32 arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_BIAS_DISABLE:
		case PIN_CONFIG_BIAS_PULL_UP:
		case PIN_CONFIG_BIAS_PULL_DOWN:
		case PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
			ret = uniphier_conf_pin_bias_set(pctldev, pin,
							 param, arg);
			break;
		case PIN_CONFIG_DRIVE_STRENGTH:
			ret = uniphier_conf_pin_drive_set(pctldev, pin, arg);
			break;
		case PIN_CONFIG_INPUT_ENABLE:
			ret = uniphier_conf_pin_input_enable(pctldev, pin, arg);
			break;
		default:
			dev_err(pctldev->dev,
				"unsupported configuration parameter %u\n",
				param);
			return -EINVAL;
		}

		if (ret)
			return ret;
	}

	return 0;
}