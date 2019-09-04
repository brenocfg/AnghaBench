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
typedef  int u32 ;
struct mthca_srq {int dummy; } ;
struct mthca_dev {int dummy; } ;
struct mthca_cqe {scalar_t__ my_qpn; int /*<<< orphan*/  wqe; } ;
struct TYPE_2__ {int cqe; } ;
struct mthca_cq {int cons_index; int /*<<< orphan*/  lock; TYPE_1__ ibcq; int /*<<< orphan*/  cqn; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTHCA_CQ_ENTRY_SIZE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 scalar_t__ cqe_sw (struct mthca_cqe*) ; 
 struct mthca_cqe* get_cqe (struct mthca_cq*,int) ; 
 scalar_t__ is_recv_cqe (struct mthca_cqe*) ; 
 int /*<<< orphan*/  memcpy (struct mthca_cqe*,struct mthca_cqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mthca_free_srq_wqe (struct mthca_srq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cqe_hw (struct mthca_cqe*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_cons_index (struct mthca_dev*,struct mthca_cq*,int) ; 
 int /*<<< orphan*/  wmb () ; 

void mthca_cq_clean(struct mthca_dev *dev, struct mthca_cq *cq, u32 qpn,
		    struct mthca_srq *srq)
{
	struct mthca_cqe *cqe;
	u32 prod_index;
	int i, nfreed = 0;

	spin_lock_irq(&cq->lock);

	/*
	 * First we need to find the current producer index, so we
	 * know where to start cleaning from.  It doesn't matter if HW
	 * adds new entries after this loop -- the QP we're worried
	 * about is already in RESET, so the new entries won't come
	 * from our QP and therefore don't need to be checked.
	 */
	for (prod_index = cq->cons_index;
	     cqe_sw(get_cqe(cq, prod_index & cq->ibcq.cqe));
	     ++prod_index)
		if (prod_index == cq->cons_index + cq->ibcq.cqe)
			break;

	if (0)
		mthca_dbg(dev, "Cleaning QPN %06x from CQN %06x; ci %d, pi %d\n",
			  qpn, cq->cqn, cq->cons_index, prod_index);

	/*
	 * Now sweep backwards through the CQ, removing CQ entries
	 * that match our QP by copying older entries on top of them.
	 */
	while ((int) --prod_index - (int) cq->cons_index >= 0) {
		cqe = get_cqe(cq, prod_index & cq->ibcq.cqe);
		if (cqe->my_qpn == cpu_to_be32(qpn)) {
			if (srq && is_recv_cqe(cqe))
				mthca_free_srq_wqe(srq, be32_to_cpu(cqe->wqe));
			++nfreed;
		} else if (nfreed)
			memcpy(get_cqe(cq, (prod_index + nfreed) & cq->ibcq.cqe),
			       cqe, MTHCA_CQ_ENTRY_SIZE);
	}

	if (nfreed) {
		for (i = 0; i < nfreed; ++i)
			set_cqe_hw(get_cqe(cq, (cq->cons_index + i) & cq->ibcq.cqe));
		wmb();
		cq->cons_index += nfreed;
		update_cons_index(dev, cq, nfreed);
	}

	spin_unlock_irq(&cq->lock);
}