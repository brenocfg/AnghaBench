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
struct TYPE_2__ {int autosuspend_delay; int /*<<< orphan*/  usage_count; scalar_t__ use_autosuspend; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPM_AUTO ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpm_idle (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpm_resume (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_autosuspend(struct device *dev, int old_delay, int old_use)
{
	int delay = dev->power.autosuspend_delay;

	/* Should runtime suspend be prevented now? */
	if (dev->power.use_autosuspend && delay < 0) {

		/* If it used to be allowed then prevent it. */
		if (!old_use || old_delay >= 0) {
			atomic_inc(&dev->power.usage_count);
			rpm_resume(dev, 0);
		}
	}

	/* Runtime suspend should be allowed now. */
	else {

		/* If it used to be prevented then allow it. */
		if (old_use && old_delay < 0)
			atomic_dec(&dev->power.usage_count);

		/* Maybe we can autosuspend now. */
		rpm_idle(dev, RPM_AUTO);
	}
}