#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct t4_cqe {int dummy; } ;
struct TYPE_6__ {TYPE_3__* qp; TYPE_4__* cq; } ;
struct ib_event {int event; TYPE_2__ element; int /*<<< orphan*/  device; } ;
struct c4iw_qp_attributes {int /*<<< orphan*/  next_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ state; } ;
struct c4iw_qp {TYPE_3__ ibqp; int /*<<< orphan*/  rhp; TYPE_1__ attr; } ;
struct c4iw_dev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct c4iw_cq {int /*<<< orphan*/  comp_handler_lock; TYPE_4__ ibcq; int /*<<< orphan*/  cq; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  C4IW_QP_ATTR_NEXT_STATE ; 
 scalar_t__ C4IW_QP_STATE_RTS ; 
 int /*<<< orphan*/  C4IW_QP_STATE_TERMINATE ; 
 int IB_EVENT_CQ_ERR ; 
 int /*<<< orphan*/  c4iw_modify_qp (int /*<<< orphan*/ ,struct c4iw_qp*,int /*<<< orphan*/ ,struct c4iw_qp_attributes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_err_cqe (struct c4iw_dev*,struct t4_cqe*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ t4_clear_cq_armed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void post_qp_event(struct c4iw_dev *dev, struct c4iw_cq *chp,
			  struct c4iw_qp *qhp,
			  struct t4_cqe *err_cqe,
			  enum ib_event_type ib_event)
{
	struct ib_event event;
	struct c4iw_qp_attributes attrs;
	unsigned long flag;

	dump_err_cqe(dev, err_cqe);

	if (qhp->attr.state == C4IW_QP_STATE_RTS) {
		attrs.next_state = C4IW_QP_STATE_TERMINATE;
		c4iw_modify_qp(qhp->rhp, qhp, C4IW_QP_ATTR_NEXT_STATE,
			       &attrs, 0);
	}

	event.event = ib_event;
	event.device = chp->ibcq.device;
	if (ib_event == IB_EVENT_CQ_ERR)
		event.element.cq = &chp->ibcq;
	else
		event.element.qp = &qhp->ibqp;
	if (qhp->ibqp.event_handler)
		(*qhp->ibqp.event_handler)(&event, qhp->ibqp.qp_context);

	if (t4_clear_cq_armed(&chp->cq)) {
		spin_lock_irqsave(&chp->comp_handler_lock, flag);
		(*chp->ibcq.comp_handler)(&chp->ibcq, chp->ibcq.cq_context);
		spin_unlock_irqrestore(&chp->comp_handler_lock, flag);
	}
}