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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct remote_event {int armed; scalar_t__ fired; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sy ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline int
remote_event_wait(wait_queue_head_t *wq, struct remote_event *event)
{
	if (!event->fired) {
		event->armed = 1;
		dsb(sy);
		if (wait_event_interruptible(*wq, event->fired)) {
			event->armed = 0;
			return 0;
		}
		event->armed = 0;
		wmb();
	}

	event->fired = 0;
	return 1;
}