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
struct lp8788_irq_data {scalar_t__* enabled; } ;
struct irq_data {size_t hwirq; } ;

/* Variables and functions */
 struct lp8788_irq_data* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void lp8788_irq_disable(struct irq_data *data)
{
	struct lp8788_irq_data *irqd = irq_data_get_irq_chip_data(data);

	irqd->enabled[data->hwirq] = 0;
}