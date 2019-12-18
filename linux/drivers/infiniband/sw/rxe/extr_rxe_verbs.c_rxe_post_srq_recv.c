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
struct TYPE_2__ {int /*<<< orphan*/  producer_lock; } ;
struct rxe_srq {TYPE_1__ rq; } ;
struct ib_srq {int dummy; } ;
struct ib_recv_wr {struct ib_recv_wr* next; } ;

/* Variables and functions */
 int post_one_recv (TYPE_1__*,struct ib_recv_wr const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rxe_srq* to_rsrq (struct ib_srq*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rxe_post_srq_recv(struct ib_srq *ibsrq, const struct ib_recv_wr *wr,
			     const struct ib_recv_wr **bad_wr)
{
	int err = 0;
	unsigned long flags;
	struct rxe_srq *srq = to_rsrq(ibsrq);

	spin_lock_irqsave(&srq->rq.producer_lock, flags);

	while (wr) {
		err = post_one_recv(&srq->rq, wr);
		if (unlikely(err))
			break;
		wr = wr->next;
	}

	spin_unlock_irqrestore(&srq->rq.producer_lock, flags);

	if (err)
		*bad_wr = wr;

	return err;
}