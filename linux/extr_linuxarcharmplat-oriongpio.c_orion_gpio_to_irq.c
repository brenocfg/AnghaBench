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
struct orion_gpio_chip {unsigned int secondary_irq_base; int /*<<< orphan*/  domain; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct orion_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int orion_gpio_to_irq(struct gpio_chip *chip, unsigned pin)
{
	struct orion_gpio_chip *ochip = gpiochip_get_data(chip);

	return irq_create_mapping(ochip->domain,
				  ochip->secondary_irq_base + pin);
}