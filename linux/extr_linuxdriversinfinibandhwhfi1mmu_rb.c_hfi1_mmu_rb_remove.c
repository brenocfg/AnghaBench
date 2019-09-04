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
struct mmu_rb_handler {int /*<<< orphan*/  ops_arg; TYPE_1__* ops; int /*<<< orphan*/  lock; int /*<<< orphan*/  root; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (int /*<<< orphan*/ ,struct mmu_rb_node*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __mmu_int_rb_remove (struct mmu_rb_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct mmu_rb_node*) ; 
 int /*<<< orphan*/  trace_hfi1_mmu_rb_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hfi1_mmu_rb_remove(struct mmu_rb_handler *handler,
			struct mmu_rb_node *node)
{
	unsigned long flags;

	/* Validity of handler and node pointers has been checked by caller. */
	trace_hfi1_mmu_rb_remove(node->addr, node->len);
	spin_lock_irqsave(&handler->lock, flags);
	__mmu_int_rb_remove(node, &handler->root);
	list_del(&node->list); /* remove from LRU list */
	spin_unlock_irqrestore(&handler->lock, flags);

	handler->ops->remove(handler->ops_arg, node);
}