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
struct davinci_gpio_controller {unsigned int gpio_unbanked; int* irqs; } ;

/* Variables and functions */
 int ENODEV ; 
 struct davinci_gpio_controller* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int gpio_to_irq_unbanked(struct gpio_chip *chip, unsigned offset)
{
	struct davinci_gpio_controller *d = gpiochip_get_data(chip);

	/*
	 * NOTE:  we assume for now that only irqs in the first gpio_chip
	 * can provide direct-mapped IRQs to AINTC (up to 32 GPIOs).
	 */
	if (offset < d->gpio_unbanked)
		return d->irqs[offset];
	else
		return -ENODEV;
}