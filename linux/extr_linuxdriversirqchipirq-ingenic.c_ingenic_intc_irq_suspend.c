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
struct irq_chip_generic {int /*<<< orphan*/  wake_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  intc_irq_set_mask (struct irq_chip_generic*,int /*<<< orphan*/ ) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 

void ingenic_intc_irq_suspend(struct irq_data *data)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	intc_irq_set_mask(gc, gc->wake_active);
}