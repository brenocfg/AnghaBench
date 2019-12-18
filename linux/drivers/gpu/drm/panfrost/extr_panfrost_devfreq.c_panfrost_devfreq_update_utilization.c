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
struct TYPE_2__ {struct panfrost_devfreq_slot* slot; int /*<<< orphan*/  devfreq; } ;
struct panfrost_device {TYPE_1__ devfreq; } ;
struct panfrost_devfreq_slot {int /*<<< orphan*/  time_last_update; int /*<<< orphan*/  idle_time; int /*<<< orphan*/  busy_time; scalar_t__ busy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panfrost_devfreq_update_utilization(struct panfrost_device *pfdev, int slot)
{
	struct panfrost_devfreq_slot *devfreq_slot = &pfdev->devfreq.slot[slot];
	ktime_t now;
	ktime_t last;

	if (!pfdev->devfreq.devfreq)
		return;

	now = ktime_get();
	last = pfdev->devfreq.slot[slot].time_last_update;

	/* If we last recorded a transition to busy, we have been idle since */
	if (devfreq_slot->busy)
		pfdev->devfreq.slot[slot].busy_time += ktime_sub(now, last);
	else
		pfdev->devfreq.slot[slot].idle_time += ktime_sub(now, last);

	pfdev->devfreq.slot[slot].time_last_update = now;
}