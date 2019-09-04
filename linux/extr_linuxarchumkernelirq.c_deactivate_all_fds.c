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
struct irq_entry {struct irq_entry* next; } ;

/* Variables and functions */
 int IGNORE_DEV ; 
 int IGNORE_IRQ ; 
 struct irq_entry* active_fds ; 
 int /*<<< orphan*/  do_free_by_irq_and_dev (struct irq_entry*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  garbage_collect_irq_entries () ; 
 int /*<<< orphan*/  irq_lock ; 
 int /*<<< orphan*/  os_close_epoll_fd () ; 
 int /*<<< orphan*/  os_set_ioignore () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int deactivate_all_fds(void)
{
	unsigned long flags;
	struct irq_entry *to_free;

	spin_lock_irqsave(&irq_lock, flags);
	/* Stop IO. The IRQ loop has no lock so this is our
	 * only way of making sure we are safe to dispose
	 * of all IRQ handlers
	 */
	os_set_ioignore();
	to_free = active_fds;
	while (to_free != NULL) {
		do_free_by_irq_and_dev(
			to_free,
			-1,
			NULL,
			IGNORE_IRQ | IGNORE_DEV
		);
		to_free = to_free->next;
	}
	garbage_collect_irq_entries();
	spin_unlock_irqrestore(&irq_lock, flags);
	os_close_epoll_fd();
	return 0;
}