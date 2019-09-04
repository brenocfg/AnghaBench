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
struct TYPE_2__ {scalar_t__ runtime_status; int /*<<< orphan*/  lock; scalar_t__ irq_safe; } ;
struct device {scalar_t__ parent; TYPE_1__ power; } ;

/* Variables and functions */
 scalar_t__ RPM_ACTIVE ; 
 int /*<<< orphan*/  pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void pm_runtime_reinit(struct device *dev)
{
	if (!pm_runtime_enabled(dev)) {
		if (dev->power.runtime_status == RPM_ACTIVE)
			pm_runtime_set_suspended(dev);
		if (dev->power.irq_safe) {
			spin_lock_irq(&dev->power.lock);
			dev->power.irq_safe = 0;
			spin_unlock_irq(&dev->power.lock);
			if (dev->parent)
				pm_runtime_put(dev->parent);
		}
	}
}