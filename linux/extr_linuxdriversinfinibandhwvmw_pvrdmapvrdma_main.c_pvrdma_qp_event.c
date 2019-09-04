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
struct ib_qp {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct pvrdma_qp {int /*<<< orphan*/  free; int /*<<< orphan*/  refcnt; struct ib_qp ibqp; } ;
struct pvrdma_dev {int /*<<< orphan*/  qp_tbl_lock; TYPE_2__* dsr; struct pvrdma_qp** qp_tbl; } ;
struct TYPE_6__ {struct ib_qp* qp; } ;
struct ib_event {int event; TYPE_3__ element; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {size_t max_qp; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvrdma_qp_event(struct pvrdma_dev *dev, u32 qpn, int type)
{
	struct pvrdma_qp *qp;
	unsigned long flags;

	spin_lock_irqsave(&dev->qp_tbl_lock, flags);
	qp = dev->qp_tbl[qpn % dev->dsr->caps.max_qp];
	if (qp)
		refcount_inc(&qp->refcnt);
	spin_unlock_irqrestore(&dev->qp_tbl_lock, flags);

	if (qp && qp->ibqp.event_handler) {
		struct ib_qp *ibqp = &qp->ibqp;
		struct ib_event e;

		e.device = ibqp->device;
		e.element.qp = ibqp;
		e.event = type; /* 1:1 mapping for now. */
		ibqp->event_handler(&e, ibqp->qp_context);
	}
	if (qp) {
		if (refcount_dec_and_test(&qp->refcnt))
			complete(&qp->free);
	}
}