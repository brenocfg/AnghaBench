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
struct TYPE_2__ {scalar_t__ disable_depth; scalar_t__ runtime_status; int /*<<< orphan*/  lock; int /*<<< orphan*/  usage_count; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RPM_ACTIVE ; 
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pm_runtime_get_if_in_use(struct device *dev)
{
	unsigned long flags;
	int retval;

	spin_lock_irqsave(&dev->power.lock, flags);
	retval = dev->power.disable_depth > 0 ? -EINVAL :
		dev->power.runtime_status == RPM_ACTIVE
			&& atomic_inc_not_zero(&dev->power.usage_count);
	spin_unlock_irqrestore(&dev->power.lock, flags);
	return retval;
}