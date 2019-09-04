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
struct nmiaction {int flags; int /*<<< orphan*/  list; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  handler; } ;
struct nmi_desc {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int EINVAL ; 
 int NMI_FLAG_FIRST ; 
 unsigned int NMI_IO_CHECK ; 
 unsigned int NMI_SERR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmi_max_handler ; 
 struct nmi_desc* nmi_to_desc (unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int __register_nmi_handler(unsigned int type, struct nmiaction *action)
{
	struct nmi_desc *desc = nmi_to_desc(type);
	unsigned long flags;

	if (!action->handler)
		return -EINVAL;

	init_irq_work(&action->irq_work, nmi_max_handler);

	raw_spin_lock_irqsave(&desc->lock, flags);

	/*
	 * Indicate if there are multiple registrations on the
	 * internal NMI handler call chains (SERR and IO_CHECK).
	 */
	WARN_ON_ONCE(type == NMI_SERR && !list_empty(&desc->head));
	WARN_ON_ONCE(type == NMI_IO_CHECK && !list_empty(&desc->head));

	/*
	 * some handlers need to be executed first otherwise a fake
	 * event confuses some handlers (kdump uses this flag)
	 */
	if (action->flags & NMI_FLAG_FIRST)
		list_add_rcu(&action->list, &desc->head);
	else
		list_add_tail_rcu(&action->list, &desc->head);
	
	raw_spin_unlock_irqrestore(&desc->lock, flags);
	return 0;
}