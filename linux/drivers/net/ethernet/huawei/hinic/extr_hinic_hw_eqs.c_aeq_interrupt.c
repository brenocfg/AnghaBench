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
struct hinic_eq_work {int /*<<< orphan*/  work; struct hinic_eq* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;
struct hinic_eq {struct hinic_eq_work aeq_work; TYPE_1__ msix_entry; int /*<<< orphan*/  hwif; } ;
struct hinic_aeqs {int /*<<< orphan*/  workq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct hinic_aeqs* aeq_to_aeqs (struct hinic_eq*) ; 
 int /*<<< orphan*/  hinic_msix_attr_cnt_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t aeq_interrupt(int irq, void *data)
{
	struct hinic_eq_work *aeq_work;
	struct hinic_eq *aeq = data;
	struct hinic_aeqs *aeqs;

	/* clear resend timer cnt register */
	hinic_msix_attr_cnt_clear(aeq->hwif, aeq->msix_entry.entry);

	aeq_work = &aeq->aeq_work;
	aeq_work->data = aeq;

	aeqs = aeq_to_aeqs(aeq);
	queue_work(aeqs->workq, &aeq_work->work);

	return IRQ_HANDLED;
}