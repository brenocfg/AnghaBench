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
struct rvt_qp {size_t state; scalar_t__ s_head; int /*<<< orphan*/  s_hlock; int /*<<< orphan*/  s_last; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* schedule_send_no_lock ) (struct rvt_qp*) ;int /*<<< orphan*/  (* do_send ) (struct rvt_qp*) ;} ;
struct rvt_dev_info {TYPE_1__ driver_f; } ;
struct ib_send_wr {struct ib_send_wr* next; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int RVT_POST_SEND_OK ; 
 int* ib_rvt_state_ops ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 struct rvt_qp* ibqp_to_rvtqp (struct ib_qp*) ; 
 int rvt_post_one_wr (struct rvt_qp*,struct ib_send_wr const*,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct rvt_qp*) ; 
 int /*<<< orphan*/  stub2 (struct rvt_qp*) ; 
 scalar_t__ unlikely (int) ; 

int rvt_post_send(struct ib_qp *ibqp, const struct ib_send_wr *wr,
		  const struct ib_send_wr **bad_wr)
{
	struct rvt_qp *qp = ibqp_to_rvtqp(ibqp);
	struct rvt_dev_info *rdi = ib_to_rvt(ibqp->device);
	unsigned long flags = 0;
	bool call_send;
	unsigned nreq = 0;
	int err = 0;

	spin_lock_irqsave(&qp->s_hlock, flags);

	/*
	 * Ensure QP state is such that we can send. If not bail out early,
	 * there is no need to do this every time we post a send.
	 */
	if (unlikely(!(ib_rvt_state_ops[qp->state] & RVT_POST_SEND_OK))) {
		spin_unlock_irqrestore(&qp->s_hlock, flags);
		return -EINVAL;
	}

	/*
	 * If the send queue is empty, and we only have a single WR then just go
	 * ahead and kick the send engine into gear. Otherwise we will always
	 * just schedule the send to happen later.
	 */
	call_send = qp->s_head == READ_ONCE(qp->s_last) && !wr->next;

	for (; wr; wr = wr->next) {
		err = rvt_post_one_wr(qp, wr, &call_send);
		if (unlikely(err)) {
			*bad_wr = wr;
			goto bail;
		}
		nreq++;
	}
bail:
	spin_unlock_irqrestore(&qp->s_hlock, flags);
	if (nreq) {
		/*
		 * Only call do_send if there is exactly one packet, and the
		 * driver said it was ok.
		 */
		if (nreq == 1 && call_send)
			rdi->driver_f.do_send(qp);
		else
			rdi->driver_f.schedule_send_no_lock(qp);
	}
	return err;
}