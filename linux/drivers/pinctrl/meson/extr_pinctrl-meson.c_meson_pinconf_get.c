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
typedef  int u16 ;
struct pinctrl_dev {int dummy; } ;
struct meson_pinctrl {int /*<<< orphan*/  dev; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 133 
#define  PIN_CONFIG_BIAS_PULL_DOWN 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_DRIVE_STRENGTH_UA 130 
#define  PIN_CONFIG_OUTPUT 129 
#define  PIN_CONFIG_OUTPUT_ENABLE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned long) ; 
 int meson_pinconf_get_drive (struct meson_pinctrl*,unsigned int) ; 
 int meson_pinconf_get_drive_strength (struct meson_pinctrl*,unsigned int,int*) ; 
 int meson_pinconf_get_output (struct meson_pinctrl*,unsigned int) ; 
 int meson_pinconf_get_pull (struct meson_pinctrl*,unsigned int) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct meson_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int meson_pinconf_get(struct pinctrl_dev *pcdev, unsigned int pin,
			     unsigned long *config)
{
	struct meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	u16 arg;
	int ret;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
	case PIN_CONFIG_BIAS_PULL_DOWN:
	case PIN_CONFIG_BIAS_PULL_UP:
		if (meson_pinconf_get_pull(pc, pin) == param)
			arg = 1;
		else
			return -EINVAL;
		break;
	case PIN_CONFIG_DRIVE_STRENGTH_UA:
		ret = meson_pinconf_get_drive_strength(pc, pin, &arg);
		if (ret)
			return ret;
		break;
	case PIN_CONFIG_OUTPUT_ENABLE:
		ret = meson_pinconf_get_output(pc, pin);
		if (ret <= 0)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_OUTPUT:
		ret = meson_pinconf_get_output(pc, pin);
		if (ret <= 0)
			return -EINVAL;

		ret = meson_pinconf_get_drive(pc, pin);
		if (ret < 0)
			return -EINVAL;

		arg = ret;
		break;

	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);
	dev_dbg(pc->dev, "pinconf for pin %u is %lu\n", pin, *config);

	return 0;
}