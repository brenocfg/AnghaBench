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
typedef  size_t uint32_t ;
struct kfd_event_waiter {int activated; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_wait (int /*<<< orphan*/ *) ; 
 struct kfd_event_waiter* kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kfd_event_waiter *alloc_event_waiters(uint32_t num_events)
{
	struct kfd_event_waiter *event_waiters;
	uint32_t i;

	event_waiters = kmalloc_array(num_events,
					sizeof(struct kfd_event_waiter),
					GFP_KERNEL);

	for (i = 0; (event_waiters) && (i < num_events) ; i++) {
		init_wait(&event_waiters[i].wait);
		event_waiters[i].activated = false;
	}

	return event_waiters;
}