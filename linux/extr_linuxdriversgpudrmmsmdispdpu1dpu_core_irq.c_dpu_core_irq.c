#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dpu_kms {TYPE_2__* hw_intr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* dispatch_irqs ) (TYPE_2__*,int /*<<< orphan*/ ,struct dpu_kms*) ;int /*<<< orphan*/  (* get_interrupt_statuses ) (TYPE_2__*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dpu_core_irq_callback_handler ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ,struct dpu_kms*) ; 

irqreturn_t dpu_core_irq(struct dpu_kms *dpu_kms)
{
	/*
	 * Read interrupt status from all sources. Interrupt status are
	 * stored within hw_intr.
	 * Function will also clear the interrupt status after reading.
	 * Individual interrupt status bit will only get stored if it
	 * is enabled.
	 */
	dpu_kms->hw_intr->ops.get_interrupt_statuses(dpu_kms->hw_intr);

	/*
	 * Dispatch to HW driver to handle interrupt lookup that is being
	 * fired. When matching interrupt is located, HW driver will call to
	 * dpu_core_irq_callback_handler with the irq_idx from the lookup table.
	 * dpu_core_irq_callback_handler will perform the registered function
	 * callback, and do the interrupt status clearing once the registered
	 * callback is finished.
	 */
	dpu_kms->hw_intr->ops.dispatch_irqs(
			dpu_kms->hw_intr,
			dpu_core_irq_callback_handler,
			dpu_kms);

	return IRQ_HANDLED;
}