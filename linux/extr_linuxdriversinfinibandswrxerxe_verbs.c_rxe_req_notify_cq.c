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
struct rxe_cq {int notify; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  queue; } ;
struct ib_cq {int dummy; } ;
typedef  enum ib_cq_notify_flags { ____Placeholder_ib_cq_notify_flags } ib_cq_notify_flags ;

/* Variables and functions */
 int IB_CQ_NEXT_COMP ; 
 int IB_CQ_REPORT_MISSED_EVENTS ; 
 int IB_CQ_SOLICITED_MASK ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rxe_cq* to_rcq (struct ib_cq*) ; 

__attribute__((used)) static int rxe_req_notify_cq(struct ib_cq *ibcq, enum ib_cq_notify_flags flags)
{
	struct rxe_cq *cq = to_rcq(ibcq);
	unsigned long irq_flags;
	int ret = 0;

	spin_lock_irqsave(&cq->cq_lock, irq_flags);
	if (cq->notify != IB_CQ_NEXT_COMP)
		cq->notify = flags & IB_CQ_SOLICITED_MASK;

	if ((flags & IB_CQ_REPORT_MISSED_EVENTS) && !queue_empty(cq->queue))
		ret = 1;

	spin_unlock_irqrestore(&cq->cq_lock, irq_flags);

	return ret;
}