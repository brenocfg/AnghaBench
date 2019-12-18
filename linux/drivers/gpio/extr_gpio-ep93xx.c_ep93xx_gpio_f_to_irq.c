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

/* Variables and functions */
 int EP93XX_GPIO_F_IRQ_BASE ; 

__attribute__((used)) static int ep93xx_gpio_f_to_irq(struct gpio_chip *gc, unsigned offset)
{
	return EP93XX_GPIO_F_IRQ_BASE + offset;
}