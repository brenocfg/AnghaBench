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
struct rxe_rq {int /*<<< orphan*/  producer_lock; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  task; } ;
struct rxe_qp {int srq; TYPE_1__ resp; int /*<<< orphan*/  valid; struct rxe_rq rq; } ;
struct ib_recv_wr {struct ib_recv_wr* next; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_QPS_INIT ; 
 scalar_t__ QP_STATE_ERROR ; 
 int post_one_recv (struct rxe_rq*,struct ib_recv_wr const*) ; 
 scalar_t__ qp_state (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rxe_qp* to_rqp (struct ib_qp*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rxe_post_recv(struct ib_qp *ibqp, const struct ib_recv_wr *wr,
			 const struct ib_recv_wr **bad_wr)
{
	int err = 0;
	struct rxe_qp *qp = to_rqp(ibqp);
	struct rxe_rq *rq = &qp->rq;
	unsigned long flags;

	if (unlikely((qp_state(qp) < IB_QPS_INIT) || !qp->valid)) {
		*bad_wr = wr;
		err = -EINVAL;
		goto err1;
	}

	if (unlikely(qp->srq)) {
		*bad_wr = wr;
		err = -EINVAL;
		goto err1;
	}

	spin_lock_irqsave(&rq->producer_lock, flags);

	while (wr) {
		err = post_one_recv(rq, wr);
		if (unlikely(err)) {
			*bad_wr = wr;
			break;
		}
		wr = wr->next;
	}

	spin_unlock_irqrestore(&rq->producer_lock, flags);

	if (qp->resp.state == QP_STATE_ERROR)
		rxe_run_task(&qp->resp.task, 1);

err1:
	return err;
}