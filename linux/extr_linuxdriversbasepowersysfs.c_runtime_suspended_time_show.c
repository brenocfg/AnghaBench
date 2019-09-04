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
struct device_attribute {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  suspended_jiffies; } ;
struct device {TYPE_1__ power; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  update_pm_runtime_accounting (struct device*) ; 

__attribute__((used)) static ssize_t runtime_suspended_time_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int ret;
	spin_lock_irq(&dev->power.lock);
	update_pm_runtime_accounting(dev);
	ret = sprintf(buf, "%i\n",
		jiffies_to_msecs(dev->power.suspended_jiffies));
	spin_unlock_irq(&dev->power.lock);
	return ret;
}