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
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;
struct hinic_eq {int /*<<< orphan*/  ceq_tasklet; TYPE_1__ msix_entry; int /*<<< orphan*/  hwif; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hinic_msix_attr_cnt_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ceq_interrupt(int irq, void *data)
{
	struct hinic_eq *ceq = data;

	/* clear resend timer cnt register */
	hinic_msix_attr_cnt_clear(ceq->hwif, ceq->msix_entry.entry);

	tasklet_schedule(&ceq->ceq_tasklet);

	return IRQ_HANDLED;
}