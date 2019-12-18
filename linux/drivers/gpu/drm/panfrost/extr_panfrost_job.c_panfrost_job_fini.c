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
struct panfrost_job_slot {TYPE_1__* queue; } ;
struct panfrost_device {struct panfrost_job_slot* js; } ;
struct TYPE_2__ {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_INT_MASK ; 
 int NUM_JOB_SLOTS ; 
 int /*<<< orphan*/  drm_sched_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  job_write (struct panfrost_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void panfrost_job_fini(struct panfrost_device *pfdev)
{
	struct panfrost_job_slot *js = pfdev->js;
	int j;

	job_write(pfdev, JOB_INT_MASK, 0);

	for (j = 0; j < NUM_JOB_SLOTS; j++)
		drm_sched_fini(&js->queue[j].sched);

}