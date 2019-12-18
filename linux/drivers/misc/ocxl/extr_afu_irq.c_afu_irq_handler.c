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
struct afu_irq {int /*<<< orphan*/  private; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocxl_afu_irq_receive (int) ; 

__attribute__((used)) static irqreturn_t afu_irq_handler(int virq, void *data)
{
	struct afu_irq *irq = (struct afu_irq *) data;

	trace_ocxl_afu_irq_receive(virq);

	if (irq->handler)
		return irq->handler(irq->private);

	return IRQ_HANDLED; // Just drop it on the ground
}