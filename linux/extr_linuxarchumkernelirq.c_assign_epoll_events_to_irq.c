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
struct irq_fd {int events; } ;
struct irq_entry {int /*<<< orphan*/  fd; struct irq_fd** irq_array; } ;

/* Variables and functions */
 int MAX_IRQ_TYPE ; 
 int os_add_epoll_fd (int,int /*<<< orphan*/ ,struct irq_entry*) ; 
 int os_del_epoll_fd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assign_epoll_events_to_irq(struct irq_entry *irq_entry)
{
	int i;
	int events = 0;
	struct irq_fd *irq;

	for (i = 0; i < MAX_IRQ_TYPE ; i++) {
		irq = irq_entry->irq_array[i];
		if (irq != NULL)
			events = irq->events | events;
	}
	if (events > 0) {
	/* os_add_epoll will call os_mod_epoll if this already exists */
		return os_add_epoll_fd(events, irq_entry->fd, irq_entry);
	}
	/* No events - delete */
	return os_del_epoll_fd(irq_entry->fd);
}