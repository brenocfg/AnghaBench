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
struct of_phandle_args {int* args; } ;
struct gpio_chip {int ngpio; } ;

/* Variables and functions */
 int EINVAL ; 
 int PINS_PER_BANK ; 

__attribute__((used)) static int sunxi_pinctrl_gpio_of_xlate(struct gpio_chip *gc,
				const struct of_phandle_args *gpiospec,
				u32 *flags)
{
	int pin, base;

	base = PINS_PER_BANK * gpiospec->args[0];
	pin = base + gpiospec->args[1];

	if (pin > gc->ngpio)
		return -EINVAL;

	if (flags)
		*flags = gpiospec->args[2];

	return pin;
}