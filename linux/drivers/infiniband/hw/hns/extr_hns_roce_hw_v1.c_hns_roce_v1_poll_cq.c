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
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;
struct hns_roce_qp {int dummy; } ;
struct hns_roce_cq {int* tptr_addr; int cons_index; int cq_depth; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  hns_roce_v1_cq_set_ci (struct hns_roce_cq*,int) ; 
 int hns_roce_v1_poll_one (struct hns_roce_cq*,struct hns_roce_qp**,struct ib_wc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hns_roce_cq* to_hr_cq (struct ib_cq*) ; 
 int /*<<< orphan*/  wmb () ; 

int hns_roce_v1_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	struct hns_roce_cq *hr_cq = to_hr_cq(ibcq);
	struct hns_roce_qp *cur_qp = NULL;
	unsigned long flags;
	int npolled;
	int ret = 0;

	spin_lock_irqsave(&hr_cq->lock, flags);

	for (npolled = 0; npolled < num_entries; ++npolled) {
		ret = hns_roce_v1_poll_one(hr_cq, &cur_qp, wc + npolled);
		if (ret)
			break;
	}

	if (npolled) {
		*hr_cq->tptr_addr = hr_cq->cons_index &
			((hr_cq->cq_depth << 1) - 1);

		/* Memroy barrier */
		wmb();
		hns_roce_v1_cq_set_ci(hr_cq, hr_cq->cons_index);
	}

	spin_unlock_irqrestore(&hr_cq->lock, flags);

	if (ret == 0 || ret == -EAGAIN)
		return npolled;
	else
		return ret;
}