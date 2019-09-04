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
struct mmu_rb_node {unsigned long addr; unsigned long len; int /*<<< orphan*/  list; } ;
struct mmu_rb_handler {int /*<<< orphan*/  lock; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mmu_int_rb_remove (struct mmu_rb_node*,int /*<<< orphan*/ *) ; 
 struct mmu_rb_node* __mmu_rb_search (struct mmu_rb_handler*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool hfi1_mmu_rb_remove_unless_exact(struct mmu_rb_handler *handler,
				     unsigned long addr, unsigned long len,
				     struct mmu_rb_node **rb_node)
{
	struct mmu_rb_node *node;
	unsigned long flags;
	bool ret = false;

	spin_lock_irqsave(&handler->lock, flags);
	node = __mmu_rb_search(handler, addr, len);
	if (node) {
		if (node->addr == addr && node->len == len)
			goto unlock;
		__mmu_int_rb_remove(node, &handler->root);
		list_del(&node->list); /* remove from LRU list */
		ret = true;
	}
unlock:
	spin_unlock_irqrestore(&handler->lock, flags);
	*rb_node = node;
	return ret;
}