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
struct TYPE_2__ {struct panfrost_devfreq_slot* slot; } ;
struct panfrost_device {TYPE_1__ devfreq; } ;
struct panfrost_devfreq_slot {int busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  panfrost_devfreq_update_utilization (struct panfrost_device*,int) ; 

void panfrost_devfreq_record_transition(struct panfrost_device *pfdev, int slot)
{
	struct panfrost_devfreq_slot *devfreq_slot = &pfdev->devfreq.slot[slot];

	panfrost_devfreq_update_utilization(pfdev, slot);
	devfreq_slot->busy = !devfreq_slot->busy;
}