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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct ocrdma_qp {int /*<<< orphan*/  rq_entry; int /*<<< orphan*/  rq_cq; int /*<<< orphan*/  srq; int /*<<< orphan*/  sq_entry; int /*<<< orphan*/  sq_cq; TYPE_1__ ibqp; } ;
struct ocrdma_dev {int /*<<< orphan*/  flush_q_lock; } ;

/* Variables and functions */
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int ocrdma_is_qp_in_rq_flushlist (int /*<<< orphan*/ ,struct ocrdma_qp*) ; 
 int ocrdma_is_qp_in_sq_flushlist (int /*<<< orphan*/ ,struct ocrdma_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ocrdma_del_flush_qp(struct ocrdma_qp *qp)
{
	int found = false;
	unsigned long flags;
	struct ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);
	/* sync with any active CQ poll */

	spin_lock_irqsave(&dev->flush_q_lock, flags);
	found = ocrdma_is_qp_in_sq_flushlist(qp->sq_cq, qp);
	if (found)
		list_del(&qp->sq_entry);
	if (!qp->srq) {
		found = ocrdma_is_qp_in_rq_flushlist(qp->rq_cq, qp);
		if (found)
			list_del(&qp->rq_entry);
	}
	spin_unlock_irqrestore(&dev->flush_q_lock, flags);
}