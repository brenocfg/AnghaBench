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
struct tps6586x_irq_data {size_t mask_reg; int /*<<< orphan*/  mask_mask; } ;
struct tps6586x {int irq_en; int /*<<< orphan*/ * mask_reg; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 struct tps6586x* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct tps6586x_irq_data* tps6586x_irqs ; 

__attribute__((used)) static void tps6586x_irq_enable(struct irq_data *irq_data)
{
	struct tps6586x *tps6586x = irq_data_get_irq_chip_data(irq_data);
	unsigned int __irq = irq_data->hwirq;
	const struct tps6586x_irq_data *data = &tps6586x_irqs[__irq];

	tps6586x->mask_reg[data->mask_reg] &= ~data->mask_mask;
	tps6586x->irq_en |= (1 << __irq);
}