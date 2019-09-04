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
typedef  size_t u16 ;
struct ocrdma_dev {struct ocrdma_cq** cq_tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct ocrdma_cq {int /*<<< orphan*/  comp_handler_lock; TYPE_1__ ibcq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 size_t OCRDMA_MAX_CQ ; 
 int /*<<< orphan*/  ocrdma_qp_buddy_cq_handler (struct ocrdma_dev*,struct ocrdma_cq*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocrdma_qp_cq_handler(struct ocrdma_dev *dev, u16 cq_idx)
{
	unsigned long flags;
	struct ocrdma_cq *cq;

	if (cq_idx >= OCRDMA_MAX_CQ)
		BUG();

	cq = dev->cq_tbl[cq_idx];
	if (cq == NULL)
		return;

	if (cq->ibcq.comp_handler) {
		spin_lock_irqsave(&cq->comp_handler_lock, flags);
		(*cq->ibcq.comp_handler) (&cq->ibcq, cq->ibcq.cq_context);
		spin_unlock_irqrestore(&cq->comp_handler_lock, flags);
	}
	ocrdma_qp_buddy_cq_handler(dev, cq);
}