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
typedef  scalar_t__ u32 ;
struct ib_cq {int dummy; } ;
struct hns_roce_wq {scalar_t__ head; scalar_t__ tail; scalar_t__ max_post; } ;
struct hns_roce_cq {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct hns_roce_cq* to_hr_cq (struct ib_cq*) ; 

bool hns_roce_wq_overflow(struct hns_roce_wq *hr_wq, int nreq,
			  struct ib_cq *ib_cq)
{
	struct hns_roce_cq *hr_cq;
	u32 cur;

	cur = hr_wq->head - hr_wq->tail;
	if (likely(cur + nreq < hr_wq->max_post))
		return false;

	hr_cq = to_hr_cq(ib_cq);
	spin_lock(&hr_cq->lock);
	cur = hr_wq->head - hr_wq->tail;
	spin_unlock(&hr_cq->lock);

	return cur + nreq >= hr_wq->max_post;
}