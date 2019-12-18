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
struct tb10x_gpio {int /*<<< orphan*/  domain; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct tb10x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int tb10x_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct tb10x_gpio *tb10x_gpio = gpiochip_get_data(chip);

	return irq_create_mapping(tb10x_gpio->domain, offset);
}