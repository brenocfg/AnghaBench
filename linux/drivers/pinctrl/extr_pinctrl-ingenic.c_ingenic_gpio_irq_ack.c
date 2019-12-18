#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int hwirq; } ;
struct ingenic_gpio_chip {TYPE_1__* jzpc; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ID_JZ4760 ; 
 scalar_t__ IRQ_TYPE_EDGE_BOTH ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_FALLING ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  JZ4740_GPIO_DATA ; 
 int /*<<< orphan*/  JZ4760_GPIO_FLAG ; 
 struct ingenic_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int ingenic_gpio_get_value (struct ingenic_gpio_chip*,int) ; 
 int /*<<< orphan*/  ingenic_gpio_set_bit (struct ingenic_gpio_chip*,int /*<<< orphan*/ ,int,int) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_type (struct ingenic_gpio_chip*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ irqd_get_trigger_type (struct irq_data*) ; 

__attribute__((used)) static void ingenic_gpio_irq_ack(struct irq_data *irqd)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	struct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	int irq = irqd->hwirq;
	bool high;

	if (irqd_get_trigger_type(irqd) == IRQ_TYPE_EDGE_BOTH) {
		/*
		 * Switch to an interrupt for the opposite edge to the one that
		 * triggered the interrupt being ACKed.
		 */
		high = ingenic_gpio_get_value(jzgc, irq);
		if (high)
			irq_set_type(jzgc, irq, IRQ_TYPE_EDGE_FALLING);
		else
			irq_set_type(jzgc, irq, IRQ_TYPE_EDGE_RISING);
	}

	if (jzgc->jzpc->version >= ID_JZ4760)
		ingenic_gpio_set_bit(jzgc, JZ4760_GPIO_FLAG, irq, false);
	else
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_DATA, irq, true);
}