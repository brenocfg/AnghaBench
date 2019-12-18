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
struct gpio_chip {int dummy; } ;
struct nmk_gpio_chip {struct gpio_chip chip; } ;

/* Variables and functions */
 struct nmk_gpio_chip* find_nmk_gpio_from_pin (unsigned int) ; 

__attribute__((used)) static struct gpio_chip *find_gc_from_pin(unsigned pin)
{
	struct nmk_gpio_chip *nmk_gpio = find_nmk_gpio_from_pin(pin);

	if (nmk_gpio)
		return &nmk_gpio->chip;
	return NULL;
}