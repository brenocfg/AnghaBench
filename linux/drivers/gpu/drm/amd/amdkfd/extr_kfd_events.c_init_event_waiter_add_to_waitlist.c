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
struct kfd_event_waiter {int /*<<< orphan*/  wait; int /*<<< orphan*/  activated; struct kfd_event* event; } ;
struct kfd_event {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_event_waiter_add_to_waitlist(struct kfd_event_waiter *waiter)
{
	struct kfd_event *ev = waiter->event;

	/* Only add to the wait list if we actually need to
	 * wait on this event.
	 */
	if (!waiter->activated)
		add_wait_queue(&ev->wq, &waiter->wait);
}