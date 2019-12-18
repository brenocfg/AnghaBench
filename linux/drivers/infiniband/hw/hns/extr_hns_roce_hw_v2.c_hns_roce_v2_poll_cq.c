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
struct hns_roce_cq {int /*<<< orphan*/  lock; int /*<<< orphan*/  cons_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_v2_cq_set_ci (struct hns_roce_cq*,int /*<<< orphan*/ ) ; 
 scalar_t__ hns_roce_v2_poll_one (struct hns_roce_cq*,struct hns_roce_qp**,struct ib_wc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hns_roce_cq* to_hr_cq (struct ib_cq*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int hns_roce_v2_poll_cq(struct ib_cq *ibcq, int num_entries,
			       struct ib_wc *wc)
{
	struct hns_roce_cq *hr_cq = to_hr_cq(ibcq);
	struct hns_roce_qp *cur_qp = NULL;
	unsigned long flags;
	int npolled;

	spin_lock_irqsave(&hr_cq->lock, flags);

	for (npolled = 0; npolled < num_entries; ++npolled) {
		if (hns_roce_v2_poll_one(hr_cq, &cur_qp, wc + npolled))
			break;
	}

	if (npolled) {
		/* Memory barrier */
		wmb();
		hns_roce_v2_cq_set_ci(hr_cq, hr_cq->cons_index);
	}

	spin_unlock_irqrestore(&hr_cq->lock, flags);

	return npolled;
}