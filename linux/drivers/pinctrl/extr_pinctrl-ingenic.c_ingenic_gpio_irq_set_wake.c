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
struct irq_data {int dummy; } ;
struct ingenic_gpio_chip {int /*<<< orphan*/  irq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct ingenic_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irq_set_irq_wake (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ingenic_gpio_irq_set_wake(struct irq_data *irqd, unsigned int on)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	struct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	return irq_set_irq_wake(jzgc->irq, on);
}