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
struct intc_irqpin_priv {int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTC_IRQPIN_REG_MASK ; 
 int /*<<< orphan*/  intc_irqpin_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  intc_irqpin_irq_write_hwirq (struct intc_irqpin_priv*,int /*<<< orphan*/ ,int) ; 
 struct intc_irqpin_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static void intc_irqpin_irq_disable(struct irq_data *d)
{
	struct intc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	int hw_irq = irqd_to_hwirq(d);

	intc_irqpin_dbg(&p->irq[hw_irq], "disable");
	intc_irqpin_irq_write_hwirq(p, INTC_IRQPIN_REG_MASK, hw_irq);
}