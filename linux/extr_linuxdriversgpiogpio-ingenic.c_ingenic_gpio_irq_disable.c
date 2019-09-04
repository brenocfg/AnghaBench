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
struct irq_data {int hwirq; } ;
struct ingenic_gpio_chip {scalar_t__ version; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ ID_JZ4770 ; 
 int /*<<< orphan*/  JZ4740_GPIO_SELECT ; 
 int /*<<< orphan*/  JZ4770_GPIO_INT ; 
 int /*<<< orphan*/  gpio_ingenic_set_bit (struct ingenic_gpio_chip*,int /*<<< orphan*/ ,int,int) ; 
 struct ingenic_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  ingenic_gpio_irq_mask (struct irq_data*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void ingenic_gpio_irq_disable(struct irq_data *irqd)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	struct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	int irq = irqd->hwirq;

	ingenic_gpio_irq_mask(irqd);

	if (jzgc->version >= ID_JZ4770)
		gpio_ingenic_set_bit(jzgc, JZ4770_GPIO_INT, irq, false);
	else
		gpio_ingenic_set_bit(jzgc, JZ4740_GPIO_SELECT, irq, false);
}