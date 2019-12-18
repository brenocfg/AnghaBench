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
struct pinctrl_dev {int dummy; } ;
struct ingenic_pinctrl {int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct TYPE_2__ {int* pull_ups; int* pull_downs; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 unsigned int PINS_PER_GPIO_CHIP ; 
#define  PIN_CONFIG_BIAS_DISABLE 130 
#define  PIN_CONFIG_BIAS_PULL_DOWN 129 
#define  PIN_CONFIG_BIAS_PULL_UP 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char,unsigned int) ; 
 int /*<<< orphan*/  ingenic_set_bias (struct ingenic_pinctrl*,unsigned int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct ingenic_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  unreachable () ; 

__attribute__((used)) static int ingenic_pinconf_set(struct pinctrl_dev *pctldev, unsigned int pin,
		unsigned long *configs, unsigned int num_configs)
{
	struct ingenic_pinctrl *jzpc = pinctrl_dev_get_drvdata(pctldev);
	unsigned int idx = pin % PINS_PER_GPIO_CHIP;
	unsigned int offt = pin / PINS_PER_GPIO_CHIP;
	unsigned int cfg;

	for (cfg = 0; cfg < num_configs; cfg++) {
		switch (pinconf_to_config_param(configs[cfg])) {
		case PIN_CONFIG_BIAS_DISABLE:
		case PIN_CONFIG_BIAS_PULL_UP:
		case PIN_CONFIG_BIAS_PULL_DOWN:
			continue;
		default:
			return -ENOTSUPP;
		}
	}

	for (cfg = 0; cfg < num_configs; cfg++) {
		switch (pinconf_to_config_param(configs[cfg])) {
		case PIN_CONFIG_BIAS_DISABLE:
			dev_dbg(jzpc->dev, "disable pull-over for pin P%c%u\n",
					'A' + offt, idx);
			ingenic_set_bias(jzpc, pin, false);
			break;

		case PIN_CONFIG_BIAS_PULL_UP:
			if (!(jzpc->info->pull_ups[offt] & BIT(idx)))
				return -EINVAL;
			dev_dbg(jzpc->dev, "set pull-up for pin P%c%u\n",
					'A' + offt, idx);
			ingenic_set_bias(jzpc, pin, true);
			break;

		case PIN_CONFIG_BIAS_PULL_DOWN:
			if (!(jzpc->info->pull_downs[offt] & BIT(idx)))
				return -EINVAL;
			dev_dbg(jzpc->dev, "set pull-down for pin P%c%u\n",
					'A' + offt, idx);
			ingenic_set_bias(jzpc, pin, true);
			break;

		default:
			unreachable();
		}
	}

	return 0;
}