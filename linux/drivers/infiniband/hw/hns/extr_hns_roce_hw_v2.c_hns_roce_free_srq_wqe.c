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
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;
struct hns_roce_srq {int /*<<< orphan*/  lock; int /*<<< orphan*/  tail; TYPE_1__ idx_que; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_roce_free_srq_wqe(struct hns_roce_srq *srq, int wqe_index)
{
	/* always called with interrupts disabled. */
	spin_lock(&srq->lock);

	bitmap_clear(srq->idx_que.bitmap, wqe_index, 1);
	srq->tail++;

	spin_unlock(&srq->lock);
}