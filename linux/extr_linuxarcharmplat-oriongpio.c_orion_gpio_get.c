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
struct orion_gpio_chip {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_DATA_IN (struct orion_gpio_chip*) ; 
 int /*<<< orphan*/  GPIO_IN_POL (struct orion_gpio_chip*) ; 
 int /*<<< orphan*/  GPIO_IO_CONF (struct orion_gpio_chip*) ; 
 int /*<<< orphan*/  GPIO_OUT (struct orion_gpio_chip*) ; 
 struct orion_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orion_gpio_get(struct gpio_chip *chip, unsigned pin)
{
	struct orion_gpio_chip *ochip = gpiochip_get_data(chip);
	int val;

	if (readl(GPIO_IO_CONF(ochip)) & (1 << pin)) {
		val = readl(GPIO_DATA_IN(ochip)) ^ readl(GPIO_IN_POL(ochip));
	} else {
		val = readl(GPIO_OUT(ochip));
	}

	return (val >> pin) & 1;
}