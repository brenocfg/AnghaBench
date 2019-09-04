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
struct nouveau_fence {int dummy; } ;
struct dma_fence {int dummy; } ;
typedef  unsigned long ktime_t ;

/* Variables and functions */
 long ERESTARTSYS ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 int NSEC_PER_MSEC ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct nouveau_fence* from_fence (struct dma_fence*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  nouveau_fence_done (struct nouveau_fence*) ; 
 int /*<<< orphan*/  schedule_hrtimeout (unsigned long*,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static long
nouveau_fence_wait_legacy(struct dma_fence *f, bool intr, long wait)
{
	struct nouveau_fence *fence = from_fence(f);
	unsigned long sleep_time = NSEC_PER_MSEC / 1000;
	unsigned long t = jiffies, timeout = t + wait;

	while (!nouveau_fence_done(fence)) {
		ktime_t kt;

		t = jiffies;

		if (wait != MAX_SCHEDULE_TIMEOUT && time_after_eq(t, timeout)) {
			__set_current_state(TASK_RUNNING);
			return 0;
		}

		__set_current_state(intr ? TASK_INTERRUPTIBLE :
					   TASK_UNINTERRUPTIBLE);

		kt = sleep_time;
		schedule_hrtimeout(&kt, HRTIMER_MODE_REL);
		sleep_time *= 2;
		if (sleep_time > NSEC_PER_MSEC)
			sleep_time = NSEC_PER_MSEC;

		if (intr && signal_pending(current))
			return -ERESTARTSYS;
	}

	__set_current_state(TASK_RUNNING);

	return timeout - t;
}