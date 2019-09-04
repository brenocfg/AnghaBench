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
struct gpio_chip {int base; int ngpio; } ;
struct orion_gpio_chip {struct gpio_chip chip; } ;

/* Variables and functions */
 int orion_gpio_chip_count ; 
 struct orion_gpio_chip* orion_gpio_chips ; 

__attribute__((used)) static struct orion_gpio_chip *orion_gpio_chip_find(int pin)
{
	int i;

	for (i = 0; i < orion_gpio_chip_count; i++) {
		struct orion_gpio_chip *ochip = orion_gpio_chips + i;
		struct gpio_chip *chip = &ochip->chip;

		if (pin >= chip->base && pin < chip->base + chip->ngpio)
			return ochip;
	}

	return NULL;
}