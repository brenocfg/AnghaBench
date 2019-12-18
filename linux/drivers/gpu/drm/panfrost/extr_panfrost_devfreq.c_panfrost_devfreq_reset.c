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
struct TYPE_4__ {TYPE_1__* slot; } ;
struct panfrost_device {TYPE_2__ devfreq; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {int /*<<< orphan*/  time_last_update; scalar_t__ idle_time; scalar_t__ busy_time; } ;

/* Variables and functions */
 int NUM_JOB_SLOTS ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void panfrost_devfreq_reset(struct panfrost_device *pfdev)
{
	ktime_t now = ktime_get();
	int i;

	for (i = 0; i < NUM_JOB_SLOTS; i++) {
		pfdev->devfreq.slot[i].busy_time = 0;
		pfdev->devfreq.slot[i].idle_time = 0;
		pfdev->devfreq.slot[i].time_last_update = now;
	}
}