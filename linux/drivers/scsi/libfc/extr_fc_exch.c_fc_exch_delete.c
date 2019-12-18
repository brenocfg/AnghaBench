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
typedef  void* u16 ;
struct fc_exch_pool {scalar_t__ total_exches; int /*<<< orphan*/  lock; void* next_index; void* right; void* left; } ;
struct fc_exch {int xid; int state; int /*<<< orphan*/  ex_list; TYPE_1__* em; struct fc_exch_pool* pool; } ;
struct TYPE_2__ {int min_xid; } ;

/* Variables and functions */
 int FC_EX_QUARANTINE ; 
 void* FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int fc_cpu_order ; 
 int /*<<< orphan*/  fc_exch_ptr_set (struct fc_exch_pool*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_exch_release (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_quarantine_exch ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_exch_delete(struct fc_exch *ep)
{
	struct fc_exch_pool *pool;
	u16 index;

	pool = ep->pool;
	spin_lock_bh(&pool->lock);
	WARN_ON(pool->total_exches <= 0);
	pool->total_exches--;

	/* update cache of free slot */
	index = (ep->xid - ep->em->min_xid) >> fc_cpu_order;
	if (!(ep->state & FC_EX_QUARANTINE)) {
		if (pool->left == FC_XID_UNKNOWN)
			pool->left = index;
		else if (pool->right == FC_XID_UNKNOWN)
			pool->right = index;
		else
			pool->next_index = index;
		fc_exch_ptr_set(pool, index, NULL);
	} else {
		fc_exch_ptr_set(pool, index, &fc_quarantine_exch);
	}
	list_del(&ep->ex_list);
	spin_unlock_bh(&pool->lock);
	fc_exch_release(ep);	/* drop hold for exch in mp */
}