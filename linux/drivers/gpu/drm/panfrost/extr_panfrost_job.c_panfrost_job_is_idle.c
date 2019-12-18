#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct panfrost_job_slot {TYPE_2__* queue; } ;
struct TYPE_8__ {TYPE_3__* slot; } ;
struct panfrost_device {TYPE_4__ devfreq; struct panfrost_job_slot* js; } ;
struct TYPE_7__ {scalar_t__ busy; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw_rq_count; } ;
struct TYPE_6__ {TYPE_1__ sched; } ;

/* Variables and functions */
 int NUM_JOB_SLOTS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

int panfrost_job_is_idle(struct panfrost_device *pfdev)
{
	struct panfrost_job_slot *js = pfdev->js;
	int i;

	for (i = 0; i < NUM_JOB_SLOTS; i++) {
		/* If there are any jobs in the HW queue, we're not idle */
		if (atomic_read(&js->queue[i].sched.hw_rq_count))
			return false;

		/* Check whether the hardware is idle */
		if (pfdev->devfreq.slot[i].busy)
			return false;
	}

	return true;
}