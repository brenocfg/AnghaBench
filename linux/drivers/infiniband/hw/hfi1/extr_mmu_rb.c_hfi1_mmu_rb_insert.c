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
struct mmu_rb_node {int /*<<< orphan*/  list; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct mmu_rb_handler {int /*<<< orphan*/  lock; int /*<<< orphan*/  root; int /*<<< orphan*/  ops_arg; TYPE_1__* ops; int /*<<< orphan*/  lru_list; } ;
struct TYPE_2__ {int (* insert ) (int /*<<< orphan*/ ,struct mmu_rb_node*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __mmu_int_rb_insert (struct mmu_rb_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __mmu_int_rb_remove (struct mmu_rb_node*,int /*<<< orphan*/ *) ; 
 struct mmu_rb_node* __mmu_rb_search (struct mmu_rb_handler*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,struct mmu_rb_node*) ; 
 int /*<<< orphan*/  trace_hfi1_mmu_rb_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hfi1_mmu_rb_insert(struct mmu_rb_handler *handler,
		       struct mmu_rb_node *mnode)
{
	struct mmu_rb_node *node;
	unsigned long flags;
	int ret = 0;

	trace_hfi1_mmu_rb_insert(mnode->addr, mnode->len);
	spin_lock_irqsave(&handler->lock, flags);
	node = __mmu_rb_search(handler, mnode->addr, mnode->len);
	if (node) {
		ret = -EINVAL;
		goto unlock;
	}
	__mmu_int_rb_insert(mnode, &handler->root);
	list_add(&mnode->list, &handler->lru_list);

	ret = handler->ops->insert(handler->ops_arg, mnode);
	if (ret) {
		__mmu_int_rb_remove(mnode, &handler->root);
		list_del(&mnode->list); /* remove from LRU list */
	}
unlock:
	spin_unlock_irqrestore(&handler->lock, flags);
	return ret;
}