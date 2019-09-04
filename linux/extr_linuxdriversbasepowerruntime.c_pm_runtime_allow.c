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
struct TYPE_2__ {int runtime_auto; int /*<<< orphan*/  lock; int /*<<< orphan*/  usage_count; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int RPM_ASYNC ; 
 int RPM_AUTO ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpm_idle (struct device*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void pm_runtime_allow(struct device *dev)
{
	spin_lock_irq(&dev->power.lock);
	if (dev->power.runtime_auto)
		goto out;

	dev->power.runtime_auto = true;
	if (atomic_dec_and_test(&dev->power.usage_count))
		rpm_idle(dev, RPM_AUTO | RPM_ASYNC);

 out:
	spin_unlock_irq(&dev->power.lock);
}