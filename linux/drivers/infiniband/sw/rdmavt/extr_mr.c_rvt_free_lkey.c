#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rvt_mregion {int lkey; int /*<<< orphan*/  refcount; scalar_t__ lkey_published; TYPE_1__* pd; } ;
struct rvt_lkey_table {int /*<<< orphan*/  lock; int /*<<< orphan*/ * table; } ;
struct TYPE_4__ {int lkey_table_size; } ;
struct rvt_dev_info {TYPE_2__ dparms; int /*<<< orphan*/  dma_mr; struct rvt_lkey_table lkey_table; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_put_mr (struct rvt_mregion*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rvt_free_lkey(struct rvt_mregion *mr)
{
	unsigned long flags;
	u32 lkey = mr->lkey;
	u32 r;
	struct rvt_dev_info *dev = ib_to_rvt(mr->pd->device);
	struct rvt_lkey_table *rkt = &dev->lkey_table;
	int freed = 0;

	spin_lock_irqsave(&rkt->lock, flags);
	if (!lkey) {
		if (mr->lkey_published) {
			mr->lkey_published = 0;
			/* insure published is written before pointer */
			rcu_assign_pointer(dev->dma_mr, NULL);
			rvt_put_mr(mr);
		}
	} else {
		if (!mr->lkey_published)
			goto out;
		r = lkey >> (32 - dev->dparms.lkey_table_size);
		mr->lkey_published = 0;
		/* insure published is written before pointer */
		rcu_assign_pointer(rkt->table[r], NULL);
	}
	freed++;
out:
	spin_unlock_irqrestore(&rkt->lock, flags);
	if (freed)
		percpu_ref_kill(&mr->refcount);
}