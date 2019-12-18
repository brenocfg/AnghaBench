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
typedef  scalar_t__ next_timeslot ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 unsigned long jiffies ; 
 unsigned long lb_interval_jiffies ; 
 int /*<<< orphan*/  lb_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int lb_throttle(void)
{
	static unsigned long last_access;
	unsigned long now, next_timeslot;
	long delay;
	int ret = 0;

	mutex_lock(&lb_mutex);

	now = jiffies;
	next_timeslot = last_access + lb_interval_jiffies;

	if (time_before(now, next_timeslot)) {
		delay = (long)(next_timeslot) - (long)now;
		set_current_state(TASK_INTERRUPTIBLE);
		if (schedule_timeout(delay) > 0) {
			/* interrupted - just abort */
			ret = -EINTR;
			goto out;
		}
		now = jiffies;
	}

	last_access = now;
out:
	mutex_unlock(&lb_mutex);

	return ret;
}