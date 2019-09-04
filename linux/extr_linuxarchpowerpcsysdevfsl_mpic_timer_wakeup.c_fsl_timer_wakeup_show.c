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
typedef  scalar_t__ time64_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ timer; } ;

/* Variables and functions */
 TYPE_1__* fsl_wakeup ; 
 int /*<<< orphan*/  mpic_get_remain_time (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sysfs_lock ; 

__attribute__((used)) static ssize_t fsl_timer_wakeup_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	time64_t interval = 0;

	mutex_lock(&sysfs_lock);
	if (fsl_wakeup->timer) {
		mpic_get_remain_time(fsl_wakeup->timer, &interval);
		interval++;
	}
	mutex_unlock(&sysfs_lock);

	return sprintf(buf, "%lld\n", interval);
}