#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long expires; } ;
struct TYPE_4__ {TYPE_1__ timer; } ;
struct drm_gpu_scheduler {unsigned long timeout; TYPE_2__ work_tdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 unsigned long jiffies ; 
 scalar_t__ mod_delayed_work (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

unsigned long drm_sched_suspend_timeout(struct drm_gpu_scheduler *sched)
{
	unsigned long sched_timeout, now = jiffies;

	sched_timeout = sched->work_tdr.timer.expires;

	/*
	 * Modify the timeout to an arbitrarily large value. This also prevents
	 * the timeout to be restarted when new submissions arrive
	 */
	if (mod_delayed_work(system_wq, &sched->work_tdr, MAX_SCHEDULE_TIMEOUT)
			&& time_after(sched_timeout, now))
		return sched_timeout - now;
	else
		return sched->timeout;
}