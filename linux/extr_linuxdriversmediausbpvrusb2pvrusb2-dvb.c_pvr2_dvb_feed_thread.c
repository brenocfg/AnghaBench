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

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int pvr2_dvb_feed_func (void*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_dvb_feed_thread(void *data)
{
	int stat = pvr2_dvb_feed_func(data);
	/* from videobuf-dvb.c: */
	while (!kthread_should_stop()) {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	}
	return stat;
}