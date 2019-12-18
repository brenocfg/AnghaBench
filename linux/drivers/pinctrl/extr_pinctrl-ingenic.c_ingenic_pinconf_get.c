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
struct ingenic_pinctrl {scalar_t__ version; TYPE_1__* info; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_2__ {int* pull_ups; int* pull_downs; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ ID_JZ4760 ; 
 int /*<<< orphan*/  JZ4740_GPIO_PULL_DIS ; 
 int /*<<< orphan*/  JZ4760_GPIO_PEN ; 
 unsigned int PINS_PER_GPIO_CHIP ; 
#define  PIN_CONFIG_BIAS_DISABLE 130 
#define  PIN_CONFIG_BIAS_PULL_DOWN 129 
#define  PIN_CONFIG_BIAS_PULL_UP 128 
 int /*<<< orphan*/  ingenic_get_pin_config (struct ingenic_pinctrl*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct ingenic_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int ingenic_pinconf_get(struct pinctrl_dev *pctldev,
		unsigned int pin, unsigned long *config)
{
	struct ingenic_pinctrl *jzpc = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	unsigned int idx = pin % PINS_PER_GPIO_CHIP;
	unsigned int offt = pin / PINS_PER_GPIO_CHIP;
	bool pull;

	if (jzpc->version >= ID_JZ4760)
		pull = !ingenic_get_pin_config(jzpc, pin, JZ4760_GPIO_PEN);
	else
		pull = !ingenic_get_pin_config(jzpc, pin, JZ4740_GPIO_PULL_DIS);

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if (pull)
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		if (!pull || !(jzpc->info->pull_ups[offt] & BIT(idx)))
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (!pull || !(jzpc->info->pull_downs[offt] & BIT(idx)))
			return -EINVAL;
		break;

	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, 1);
	return 0;
}