#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct sunxi_pinctrl {int membase; TYPE_1__* desc; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_2__ {scalar_t__ pin_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_STRENGTH 128 
 int SUN4I_PINCTRL_NO_PULL ; 
 int SUN4I_PINCTRL_PULL_DOWN ; 
 int SUN4I_PINCTRL_PULL_UP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct sunxi_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl (int) ; 
 int sunxi_pconf_reg (unsigned int,int,int*,int*,int*) ; 

__attribute__((used)) static int sunxi_pconf_get(struct pinctrl_dev *pctldev, unsigned pin,
			   unsigned long *config)
{
	struct sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	u32 offset, shift, mask, val;
	u16 arg;
	int ret;

	pin -= pctl->desc->pin_base;

	ret = sunxi_pconf_reg(pin, param, &offset, &shift, &mask);
	if (ret < 0)
		return ret;

	val = (readl(pctl->membase + offset) >> shift) & mask;

	switch (pinconf_to_config_param(*config)) {
	case PIN_CONFIG_DRIVE_STRENGTH:
		arg = (val + 1) * 10;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		if (val != SUN4I_PINCTRL_PULL_UP)
			return -EINVAL;
		arg = 1; /* hardware is weak pull-up */
		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (val != SUN4I_PINCTRL_PULL_DOWN)
			return -EINVAL;
		arg = 1; /* hardware is weak pull-down */
		break;

	case PIN_CONFIG_BIAS_DISABLE:
		if (val != SUN4I_PINCTRL_NO_PULL)
			return -EINVAL;
		arg = 0;
		break;

	default:
		/* sunxi_pconf_reg should catch anything unsupported */
		WARN_ON(1);
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}