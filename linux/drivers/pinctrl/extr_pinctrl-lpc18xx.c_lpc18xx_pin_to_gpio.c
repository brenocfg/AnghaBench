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
struct pinctrl_gpio_range {unsigned int pin_base; unsigned int base; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin_nolock (struct pinctrl_dev*,unsigned int) ; 

__attribute__((used)) static int lpc18xx_pin_to_gpio(struct pinctrl_dev *pctldev, unsigned pin)
{
	struct pinctrl_gpio_range *range;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	if (!range)
		return -EINVAL;

	return pin - range->pin_base + range->base;
}