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
struct thunderx_gpio {int /*<<< orphan*/  irqd; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct thunderx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int thunderx_gpio_to_irq(struct gpio_chip *chip, unsigned int offset)
{
	struct thunderx_gpio *txgpio = gpiochip_get_data(chip);

	return irq_find_mapping(txgpio->irqd, offset);
}