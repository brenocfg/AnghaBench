#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct pvrdma_dev {int /*<<< orphan*/  cq_tbl_lock; TYPE_2__* dsr; struct pvrdma_cq** cq_tbl; } ;
struct ib_cq {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct pvrdma_cq {int /*<<< orphan*/  free; int /*<<< orphan*/  refcnt; struct ib_cq ibcq; } ;
struct TYPE_6__ {struct ib_cq* cq; } ;
struct ib_event {int event; TYPE_3__ element; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {size_t max_cq; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvrdma_cq_event(struct pvrdma_dev *dev, u32 cqn, int type)
{
	struct pvrdma_cq *cq;
	unsigned long flags;

	spin_lock_irqsave(&dev->cq_tbl_lock, flags);
	cq = dev->cq_tbl[cqn % dev->dsr->caps.max_cq];
	if (cq)
		refcount_inc(&cq->refcnt);
	spin_unlock_irqrestore(&dev->cq_tbl_lock, flags);

	if (cq && cq->ibcq.event_handler) {
		struct ib_cq *ibcq = &cq->ibcq;
		struct ib_event e;

		e.device = ibcq->device;
		e.element.cq = ibcq;
		e.event = type; /* 1:1 mapping for now. */
		ibcq->event_handler(&e, ibcq->cq_context);
	}
	if (cq) {
		if (refcount_dec_and_test(&cq->refcnt))
			complete(&cq->free);
	}
}