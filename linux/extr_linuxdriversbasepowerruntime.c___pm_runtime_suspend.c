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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_safe; int /*<<< orphan*/  usage_count; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int RPM_ASYNC ; 
 int RPM_GET_PUT ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int rpm_suspend (struct device*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int __pm_runtime_suspend(struct device *dev, int rpmflags)
{
	unsigned long flags;
	int retval;

	if (rpmflags & RPM_GET_PUT) {
		if (!atomic_dec_and_test(&dev->power.usage_count))
			return 0;
	}

	might_sleep_if(!(rpmflags & RPM_ASYNC) && !dev->power.irq_safe);

	spin_lock_irqsave(&dev->power.lock, flags);
	retval = rpm_suspend(dev, rpmflags);
	spin_unlock_irqrestore(&dev->power.lock, flags);

	return retval;
}