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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  recv_cq; } ;
struct c4iw_qp {int /*<<< orphan*/  lock; int /*<<< orphan*/  wq; TYPE_1__ ibqp; } ;
struct c4iw_cq {int /*<<< orphan*/  lock; int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_recv_cqe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct c4iw_cq* to_c4iw_cq (int /*<<< orphan*/ ) ; 

void c4iw_flush_srqidx(struct c4iw_qp *qhp, u32 srqidx)
{
	struct c4iw_cq *rchp = to_c4iw_cq(qhp->ibqp.recv_cq);
	unsigned long flag;

	/* locking heirarchy: cq lock first, then qp lock. */
	spin_lock_irqsave(&rchp->lock, flag);
	spin_lock(&qhp->lock);

	/* create a SRQ RECV CQE for srqidx */
	insert_recv_cqe(&qhp->wq, &rchp->cq, srqidx);

	spin_unlock(&qhp->lock);
	spin_unlock_irqrestore(&rchp->lock, flag);
}