#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int send_flags; int /*<<< orphan*/  opcode; } ;
struct rxe_send_wqe {scalar_t__ state; TYPE_5__ wr; int /*<<< orphan*/  mask; } ;
struct TYPE_9__ {scalar_t__ state; scalar_t__ wqe_index; int wait_fence; } ;
struct TYPE_8__ {int /*<<< orphan*/  queue; } ;
struct TYPE_7__ {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct rxe_qp {TYPE_4__ req; TYPE_3__ sq; TYPE_2__ ibqp; int /*<<< orphan*/  state_lock; } ;
struct TYPE_6__ {TYPE_2__* qp; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_SQ_DRAINED ; 
 int IB_SEND_FENCE ; 
 scalar_t__ QP_STATE_DRAIN ; 
 scalar_t__ QP_STATE_DRAINED ; 
 struct rxe_send_wqe* addr_from_index (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ consumer_index (int /*<<< orphan*/ ) ; 
 scalar_t__ producer_index (int /*<<< orphan*/ ) ; 
 struct rxe_send_wqe* queue_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wqe_state_posted ; 
 scalar_t__ wqe_state_processing ; 
 int /*<<< orphan*/  wr_opcode_mask (int /*<<< orphan*/ ,struct rxe_qp*) ; 

__attribute__((used)) static struct rxe_send_wqe *req_next_wqe(struct rxe_qp *qp)
{
	struct rxe_send_wqe *wqe = queue_head(qp->sq.queue);
	unsigned long flags;

	if (unlikely(qp->req.state == QP_STATE_DRAIN)) {
		/* check to see if we are drained;
		 * state_lock used by requester and completer
		 */
		spin_lock_irqsave(&qp->state_lock, flags);
		do {
			if (qp->req.state != QP_STATE_DRAIN) {
				/* comp just finished */
				spin_unlock_irqrestore(&qp->state_lock,
						       flags);
				break;
			}

			if (wqe && ((qp->req.wqe_index !=
				consumer_index(qp->sq.queue)) ||
				(wqe->state != wqe_state_posted))) {
				/* comp not done yet */
				spin_unlock_irqrestore(&qp->state_lock,
						       flags);
				break;
			}

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
		} while (0);
	}

	if (qp->req.wqe_index == producer_index(qp->sq.queue))
		return NULL;

	wqe = addr_from_index(qp->sq.queue, qp->req.wqe_index);

	if (unlikely((qp->req.state == QP_STATE_DRAIN ||
		      qp->req.state == QP_STATE_DRAINED) &&
		     (wqe->state != wqe_state_processing)))
		return NULL;

	if (unlikely((wqe->wr.send_flags & IB_SEND_FENCE) &&
		     (qp->req.wqe_index != consumer_index(qp->sq.queue)))) {
		qp->req.wait_fence = 1;
		return NULL;
	}

	wqe->mask = wr_opcode_mask(wqe->wr.opcode, qp);
	return wqe;
}