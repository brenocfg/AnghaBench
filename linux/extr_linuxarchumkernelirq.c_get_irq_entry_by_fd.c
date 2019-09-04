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
struct irq_entry {int fd; struct irq_entry* next; } ;

/* Variables and functions */
 struct irq_entry* active_fds ; 

__attribute__((used)) static struct irq_entry *get_irq_entry_by_fd(int fd)
{
	struct irq_entry *walk = active_fds;

	while (walk != NULL) {
		if (walk->fd == fd)
			return walk;
		walk = walk->next;
	}
	return NULL;
}