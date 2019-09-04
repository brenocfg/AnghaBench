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
struct rxe_send_wqe {scalar_t__ has_rd_atomic; } ;
struct TYPE_8__ {scalar_t__ psn; scalar_t__ timeout_retry; } ;
struct TYPE_7__ {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct TYPE_5__ {scalar_t__ state; scalar_t__ psn; int /*<<< orphan*/  task; scalar_t__ need_rd_atomic; int /*<<< orphan*/  rd_atomic; } ;
struct rxe_qp {TYPE_4__ comp; int /*<<< orphan*/  state_lock; TYPE_3__ ibqp; TYPE_1__ req; } ;
struct rxe_pkt_info {int /*<<< orphan*/  psn; } ;
struct TYPE_6__ {TYPE_3__* qp; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_2__ element; int /*<<< orphan*/  device; } ;
typedef  enum comp_state { ____Placeholder_comp_state } comp_state ;

/* Variables and functions */
 int COMPST_DONE ; 
 int COMPST_UPDATE_COMP ; 
 int /*<<< orphan*/  IB_EVENT_SQ_DRAINED ; 
 scalar_t__ QP_STATE_DRAIN ; 
 scalar_t__ QP_STATE_DRAINED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_complete (struct rxe_qp*,struct rxe_send_wqe*) ; 
 scalar_t__ psn_compare (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline enum comp_state complete_ack(struct rxe_qp *qp,
					   struct rxe_pkt_info *pkt,
					   struct rxe_send_wqe *wqe)
{
	unsigned long flags;

	if (wqe->has_rd_atomic) {
		wqe->has_rd_atomic = 0;
		atomic_inc(&qp->req.rd_atomic);
		if (qp->req.need_rd_atomic) {
			qp->comp.timeout_retry = 0;
			qp->req.need_rd_atomic = 0;
			rxe_run_task(&qp->req.task, 1);
		}
	}

	if (unlikely(qp->req.state == QP_STATE_DRAIN)) {
		/* state_lock used by requester & completer */
		spin_lock_irqsave(&qp->state_lock, flags);
		if ((qp->req.state == QP_STATE_DRAIN) &&
		    (qp->comp.psn == qp->req.psn)) {
			qp->req.state = QP_STATE_DRAINED;
			spin_unlock_irqrestore(&qp->state_lock, flags);

			if (qp->ibqp.event_handler) {
				struct ib_event ev;

				ev.device = qp->ibqp.device;
				ev.element.qp = &qp->ibqp;
				ev.event = IB_EVENT_SQ_DRAINED;
				qp->ibqp.event_handler(&ev,
					qp->ibqp.qp_context);
			}
		} else {
			spin_unlock_irqrestore(&qp->state_lock, flags);
		}
	}

	do_complete(qp, wqe);

	if (psn_compare(pkt->psn, qp->comp.psn) >= 0)
		return COMPST_UPDATE_COMP;
	else
		return COMPST_DONE;
}