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
struct sunxi_pinctrl {int membase; int /*<<< orphan*/  lock; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_STRENGTH 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct sunxi_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (int) ; 
 int sunxi_pconf_reg (unsigned int,int,int*,int*,int*) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int sunxi_pconf_set(struct pinctrl_dev *pctldev, unsigned pin,
			   unsigned long *configs, unsigned num_configs)
{
	struct sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	int i;

	for (i = 0; i < num_configs; i++) {
		enum pin_config_param param;
		unsigned long flags;
		u32 offset, shift, mask, reg;
		u32 arg, val;
		int ret;

		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		ret = sunxi_pconf_reg(pin, param, &offset, &shift, &mask);
		if (ret < 0)
			return ret;

		switch (param) {
		case PIN_CONFIG_DRIVE_STRENGTH:
			if (arg < 10 || arg > 40)
				return -EINVAL;
			/*
			 * We convert from mA to what the register expects:
			 *   0: 10mA
			 *   1: 20mA
			 *   2: 30mA
			 *   3: 40mA
			 */
			val = arg / 10 - 1;
			break;
		case PIN_CONFIG_BIAS_DISABLE:
			val = 0;
			break;
		case PIN_CONFIG_BIAS_PULL_UP:
			if (arg == 0)
				return -EINVAL;
			val = 1;
			break;
		case PIN_CONFIG_BIAS_PULL_DOWN:
			if (arg == 0)
				return -EINVAL;
			val = 2;
			break;
		default:
			/* sunxi_pconf_reg should catch anything unsupported */
			WARN_ON(1);
			return -ENOTSUPP;
		}

		raw_spin_lock_irqsave(&pctl->lock, flags);
		reg = readl(pctl->membase + offset);
		reg &= ~(mask << shift);
		writel(reg | val << shift, pctl->membase + offset);
		raw_spin_unlock_irqrestore(&pctl->lock, flags);
	} /* for each config */

	return 0;
}