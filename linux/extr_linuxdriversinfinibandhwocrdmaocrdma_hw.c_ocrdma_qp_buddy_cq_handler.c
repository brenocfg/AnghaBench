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
struct ocrdma_dev {int /*<<< orphan*/  flush_q_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct ocrdma_cq {int /*<<< orphan*/  comp_handler_lock; TYPE_1__ ibcq; } ;

/* Variables and functions */
 struct ocrdma_cq* _ocrdma_qp_buddy_cq_handler (struct ocrdma_dev*,struct ocrdma_cq*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocrdma_qp_buddy_cq_handler(struct ocrdma_dev *dev,
				       struct ocrdma_cq *cq)
{
	unsigned long flags;
	struct ocrdma_cq *bcq = NULL;

	/* Go through list of QPs in error state which are using this CQ
	 * and invoke its callback handler to trigger CQE processing for
	 * error/flushed CQE. It is rare to find more than few entries in
	 * this list as most consumers stops after getting error CQE.
	 * List is traversed only once when a matching buddy cq found for a QP.
	 */
	spin_lock_irqsave(&dev->flush_q_lock, flags);
	/* Check if buddy CQ is present.
	 * true - Check for  SQ CQ
	 * false - Check for RQ CQ
	 */
	bcq = _ocrdma_qp_buddy_cq_handler(dev, cq, true);
	if (bcq == NULL)
		bcq = _ocrdma_qp_buddy_cq_handler(dev, cq, false);
	spin_unlock_irqrestore(&dev->flush_q_lock, flags);

	/* if there is valid buddy cq, look for its completion handler */
	if (bcq && bcq->ibcq.comp_handler) {
		spin_lock_irqsave(&bcq->comp_handler_lock, flags);
		(*bcq->ibcq.comp_handler) (&bcq->ibcq, bcq->ibcq.cq_context);
		spin_unlock_irqrestore(&bcq->comp_handler_lock, flags);
	}
}