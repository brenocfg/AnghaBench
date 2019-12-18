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
struct TYPE_4__ {int /*<<< orphan*/  devfreq; TYPE_1__* slot; } ;
struct panfrost_device {TYPE_2__ devfreq; } ;
struct TYPE_3__ {int busy; } ;

/* Variables and functions */
 int NUM_JOB_SLOTS ; 
 int /*<<< orphan*/  devfreq_resume_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panfrost_devfreq_reset (struct panfrost_device*) ; 

void panfrost_devfreq_resume(struct panfrost_device *pfdev)
{
	int i;

	if (!pfdev->devfreq.devfreq)
		return;

	panfrost_devfreq_reset(pfdev);
	for (i = 0; i < NUM_JOB_SLOTS; i++)
		pfdev->devfreq.slot[i].busy = false;

	devfreq_resume_device(pfdev->devfreq.devfreq);
}