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
 int ENOTSUPP ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin (struct pinctrl_dev*,unsigned int) ; 
 int u300_gpio_config_get (int /*<<< orphan*/ ,unsigned int,unsigned long*) ; 

__attribute__((used)) static int u300_pin_config_get(struct pinctrl_dev *pctldev, unsigned pin,
			       unsigned long *config)
{
	struct pinctrl_gpio_range *range =
		pinctrl_find_gpio_range_from_pin(pctldev, pin);

	/* We get config for those pins we CAN get it for and that's it */
	if (!range)
		return -ENOTSUPP;

	return u300_gpio_config_get(range->gc,
				    (pin - range->pin_base + range->base),
				    config);
}