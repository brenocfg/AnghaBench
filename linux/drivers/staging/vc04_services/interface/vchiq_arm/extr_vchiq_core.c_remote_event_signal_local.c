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
struct remote_event {int fired; scalar_t__ armed; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
remote_event_signal_local(wait_queue_head_t *wq, struct remote_event *event)
{
	event->fired = 1;
	event->armed = 0;
	wake_up_all(wq);
}