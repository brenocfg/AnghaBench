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
struct gpio_chip {unsigned int base; } ;

/* Variables and functions */
 int EINVAL ; 
 int EP93XX_GPIO_LINE_MAX_IRQ ; 

__attribute__((used)) static int ep93xx_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	int gpio = chip->base + offset;

	if (gpio > EP93XX_GPIO_LINE_MAX_IRQ)
		return -EINVAL;

	return 64 + gpio;
}