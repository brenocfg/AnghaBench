#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rxe_sq {int /*<<< orphan*/  sq_lock; int /*<<< orphan*/  queue; } ;
struct rxe_send_wqe {int dummy; } ;
struct rxe_qp {struct rxe_sq sq; } ;
struct ib_send_wr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  advance_producer (int /*<<< orphan*/ ) ; 
 int init_send_wqe (struct rxe_qp*,struct ib_send_wr const*,unsigned int,int /*<<< orphan*/ ,struct rxe_send_wqe*) ; 
 struct rxe_send_wqe* producer_addr (int /*<<< orphan*/ ) ; 
 int queue_full (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int validate_send_wr (struct rxe_qp*,struct ib_send_wr const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int post_one_send(struct rxe_qp *qp, const struct ib_send_wr *ibwr,
			 unsigned int mask, u32 length)
{
	int err;
	struct rxe_sq *sq = &qp->sq;
	struct rxe_send_wqe *send_wqe;
	unsigned long flags;

	err = validate_send_wr(qp, ibwr, mask, length);
	if (err)
		return err;

	spin_lock_irqsave(&qp->sq.sq_lock, flags);

	if (unlikely(queue_full(sq->queue))) {
		err = -ENOMEM;
		goto err1;
	}

	send_wqe = producer_addr(sq->queue);

	err = init_send_wqe(qp, ibwr, mask, length, send_wqe);
	if (unlikely(err))
		goto err1;

	/*
	 * make sure all changes to the work queue are
	 * written before we update the producer pointer
	 */
	smp_wmb();

	advance_producer(sq->queue);
	spin_unlock_irqrestore(&qp->sq.sq_lock, flags);

	return 0;

err1:
	spin_unlock_irqrestore(&qp->sq.sq_lock, flags);
	return err;
}