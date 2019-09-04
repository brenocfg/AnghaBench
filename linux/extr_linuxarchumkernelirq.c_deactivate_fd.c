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
struct irq_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE_DEV ; 
 int /*<<< orphan*/  do_free_by_irq_and_dev (struct irq_entry*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garbage_collect_irq_entries () ; 
 struct irq_entry* get_irq_entry_by_fd (int) ; 
 int /*<<< orphan*/  ignore_sigio_fd (int) ; 
 int /*<<< orphan*/  irq_lock ; 
 int /*<<< orphan*/  os_del_epoll_fd (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void deactivate_fd(int fd, int irqnum)
{
	struct irq_entry *to_free;
	unsigned long flags;

	os_del_epoll_fd(fd);
	spin_lock_irqsave(&irq_lock, flags);
	to_free = get_irq_entry_by_fd(fd);
	if (to_free != NULL) {
		do_free_by_irq_and_dev(
			to_free,
			irqnum,
			NULL,
			IGNORE_DEV
		);
	}
	garbage_collect_irq_entries();
	spin_unlock_irqrestore(&irq_lock, flags);
	ignore_sigio_fd(fd);
}