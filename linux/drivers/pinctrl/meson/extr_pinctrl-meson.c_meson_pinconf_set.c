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
struct pinctrl_dev {int dummy; } ;
struct meson_pinctrl {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 133 
#define  PIN_CONFIG_BIAS_PULL_DOWN 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_DRIVE_STRENGTH_UA 130 
#define  PIN_CONFIG_OUTPUT 129 
#define  PIN_CONFIG_OUTPUT_ENABLE 128 
 int meson_pinconf_disable_bias (struct meson_pinctrl*,unsigned int) ; 
 int meson_pinconf_enable_bias (struct meson_pinctrl*,unsigned int,int) ; 
 int meson_pinconf_set_drive_strength (struct meson_pinctrl*,unsigned int,unsigned int) ; 
 int meson_pinconf_set_output (struct meson_pinctrl*,unsigned int,unsigned int) ; 
 int meson_pinconf_set_output_drive (struct meson_pinctrl*,unsigned int,unsigned int) ; 
 unsigned int pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct meson_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int meson_pinconf_set(struct pinctrl_dev *pcdev, unsigned int pin,
			     unsigned long *configs, unsigned num_configs)
{
	struct meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	enum pin_config_param param;
	unsigned int arg = 0;
	int i, ret;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);

		switch (param) {
		case PIN_CONFIG_DRIVE_STRENGTH_UA:
		case PIN_CONFIG_OUTPUT_ENABLE:
		case PIN_CONFIG_OUTPUT:
			arg = pinconf_to_config_argument(configs[i]);
			break;

		default:
			break;
		}

		switch (param) {
		case PIN_CONFIG_BIAS_DISABLE:
			ret = meson_pinconf_disable_bias(pc, pin);
			break;
		case PIN_CONFIG_BIAS_PULL_UP:
			ret = meson_pinconf_enable_bias(pc, pin, true);
			break;
		case PIN_CONFIG_BIAS_PULL_DOWN:
			ret = meson_pinconf_enable_bias(pc, pin, false);
			break;
		case PIN_CONFIG_DRIVE_STRENGTH_UA:
			ret = meson_pinconf_set_drive_strength(pc, pin, arg);
			break;
		case PIN_CONFIG_OUTPUT_ENABLE:
			ret = meson_pinconf_set_output(pc, pin, arg);
			break;
		case PIN_CONFIG_OUTPUT:
			ret = meson_pinconf_set_output_drive(pc, pin, arg);
			break;
		default:
			ret = -ENOTSUPP;
		}

		if (ret)
			return ret;
	}

	return 0;
}