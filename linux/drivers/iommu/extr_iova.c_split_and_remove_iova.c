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
struct iova_domain {int /*<<< orphan*/  iova_rbtree_lock; int /*<<< orphan*/  rbroot; } ;
struct iova {unsigned long pfn_lo; unsigned long pfn_hi; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cached_rbnode_delete_update (struct iova_domain*,struct iova*) ; 
 struct iova* alloc_and_init_iova (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  free_iova_mem (struct iova*) ; 
 int /*<<< orphan*/  iova_insert_rbtree (int /*<<< orphan*/ *,struct iova*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct iova *
split_and_remove_iova(struct iova_domain *iovad, struct iova *iova,
		      unsigned long pfn_lo, unsigned long pfn_hi)
{
	unsigned long flags;
	struct iova *prev = NULL, *next = NULL;

	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);
	if (iova->pfn_lo < pfn_lo) {
		prev = alloc_and_init_iova(iova->pfn_lo, pfn_lo - 1);
		if (prev == NULL)
			goto error;
	}
	if (iova->pfn_hi > pfn_hi) {
		next = alloc_and_init_iova(pfn_hi + 1, iova->pfn_hi);
		if (next == NULL)
			goto error;
	}

	__cached_rbnode_delete_update(iovad, iova);
	rb_erase(&iova->node, &iovad->rbroot);

	if (prev) {
		iova_insert_rbtree(&iovad->rbroot, prev, NULL);
		iova->pfn_lo = pfn_lo;
	}
	if (next) {
		iova_insert_rbtree(&iovad->rbroot, next, NULL);
		iova->pfn_hi = pfn_hi;
	}
	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);

	return iova;

error:
	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);
	if (prev)
		free_iova_mem(prev);
	return NULL;
}