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
struct irq_data {int dummy; } ;
struct intc_irqpin_priv {int /*<<< orphan*/  wakeup_path; TYPE_1__* irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  requested_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct intc_irqpin_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_irq_wake (int /*<<< orphan*/ ,unsigned int) ; 
 int irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static int intc_irqpin_irq_set_wake(struct irq_data *d, unsigned int on)
{
	struct intc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	int hw_irq = irqd_to_hwirq(d);

	irq_set_irq_wake(p->irq[hw_irq].requested_irq, on);
	if (on)
		atomic_inc(&p->wakeup_path);
	else
		atomic_dec(&p->wakeup_path);

	return 0;
}