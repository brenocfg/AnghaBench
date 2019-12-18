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
struct pinctrl_gpio_range {unsigned int pin_base; unsigned int base; int /*<<< orphan*/  gc; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pinconf_to_config_param (unsigned long) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin (struct pinctrl_dev*,unsigned int) ; 
 int u300_gpio_config_set (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u300_pin_config_set(struct pinctrl_dev *pctldev, unsigned pin,
			       unsigned long *configs, unsigned num_configs)
{
	struct pinctrl_gpio_range *range =
		pinctrl_find_gpio_range_from_pin(pctldev, pin);
	int ret, i;

	if (!range)
		return -EINVAL;

	for (i = 0; i < num_configs; i++) {
		/* Note: none of these configurations take any argument */
		ret = u300_gpio_config_set(range->gc,
			(pin - range->pin_base + range->base),
			pinconf_to_config_param(configs[i]));
		if (ret)
			return ret;
	} /* for each config */

	return 0;
}