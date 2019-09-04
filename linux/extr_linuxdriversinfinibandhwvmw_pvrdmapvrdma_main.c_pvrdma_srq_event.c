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
struct ib_srq {int /*<<< orphan*/  srq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct pvrdma_srq {int /*<<< orphan*/  free; int /*<<< orphan*/  refcnt; struct ib_srq ibsrq; } ;
struct pvrdma_dev {int /*<<< orphan*/  srq_tbl_lock; TYPE_2__* dsr; struct pvrdma_srq** srq_tbl; } ;
struct TYPE_6__ {struct ib_srq* srq; } ;
struct ib_event {int event; TYPE_3__ element; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {size_t max_srq; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvrdma_srq_event(struct pvrdma_dev *dev, u32 srqn, int type)
{
	struct pvrdma_srq *srq;
	unsigned long flags;

	spin_lock_irqsave(&dev->srq_tbl_lock, flags);
	if (dev->srq_tbl)
		srq = dev->srq_tbl[srqn % dev->dsr->caps.max_srq];
	else
		srq = NULL;
	if (srq)
		refcount_inc(&srq->refcnt);
	spin_unlock_irqrestore(&dev->srq_tbl_lock, flags);

	if (srq && srq->ibsrq.event_handler) {
		struct ib_srq *ibsrq = &srq->ibsrq;
		struct ib_event e;

		e.device = ibsrq->device;
		e.element.srq = ibsrq;
		e.event = type; /* 1:1 mapping for now. */
		ibsrq->event_handler(&e, ibsrq->srq_context);
	}
	if (srq) {
		if (refcount_dec_and_test(&srq->refcnt))
			complete(&srq->free);
	}
}