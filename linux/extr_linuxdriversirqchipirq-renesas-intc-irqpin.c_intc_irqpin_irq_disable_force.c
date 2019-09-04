#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int dummy; } ;
struct intc_irqpin_priv {TYPE_1__* irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* irq_mask ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int requested_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  intc_irqpin_irq_disable (struct irq_data*) ; 
 struct intc_irqpin_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 TYPE_2__* irq_get_chip (int) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 size_t irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intc_irqpin_irq_disable_force(struct irq_data *d)
{
	struct intc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	int irq = p->irq[irqd_to_hwirq(d)].requested_irq;

	/* disable interrupt through parent interrupt controller,
	 * assumes non-shared interrupt with 1:1 mapping
	 * needed for busted IRQs on some SoCs like sh73a0
	 */
	irq_get_chip(irq)->irq_mask(irq_get_irq_data(irq));
	intc_irqpin_irq_disable(d);
}