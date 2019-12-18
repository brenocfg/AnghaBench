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
struct xpc_fifo_head_uv {int /*<<< orphan*/  lock; int /*<<< orphan*/  n_entries; struct xpc_fifo_entry_uv* last; struct xpc_fifo_entry_uv* first; } ;
struct xpc_fifo_entry_uv {struct xpc_fifo_entry_uv* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
xpc_put_fifo_entry_uv(struct xpc_fifo_head_uv *head,
		      struct xpc_fifo_entry_uv *last)
{
	unsigned long irq_flags;

	last->next = NULL;
	spin_lock_irqsave(&head->lock, irq_flags);
	if (head->last != NULL)
		head->last->next = last;
	else
		head->first = last;
	head->last = last;
	head->n_entries++;
	spin_unlock_irqrestore(&head->lock, irq_flags);
}