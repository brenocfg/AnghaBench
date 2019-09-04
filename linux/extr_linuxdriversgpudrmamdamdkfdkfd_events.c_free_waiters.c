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
typedef  size_t uint32_t ;
struct kfd_event_waiter {int /*<<< orphan*/  wait; TYPE_1__* event; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct kfd_event_waiter*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_waiters(uint32_t num_events, struct kfd_event_waiter *waiters)
{
	uint32_t i;

	for (i = 0; i < num_events; i++)
		if (waiters[i].event)
			remove_wait_queue(&waiters[i].event->wq,
					  &waiters[i].wait);

	kfree(waiters);
}