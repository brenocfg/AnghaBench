#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cosm_device {int sysfs_heartbeat_enable; scalar_t__ state; int heartbeat_watchdog_enable; int /*<<< orphan*/  cosm_mutex; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MIC_ONLINE ; 
 struct cosm_device* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
heartbeat_enable_store(struct device *dev,
		       struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct cosm_device *cdev = dev_get_drvdata(dev);
	int enable;
	int ret;

	if (!cdev)
		return -EINVAL;

	mutex_lock(&cdev->cosm_mutex);
	ret = kstrtoint(buf, 10, &enable);
	if (ret)
		goto unlock;

	cdev->sysfs_heartbeat_enable = enable;
	/* if state is not online, cdev->heartbeat_watchdog_enable is 0 */
	if (cdev->state == MIC_ONLINE)
		cdev->heartbeat_watchdog_enable = enable;
	ret = count;
unlock:
	mutex_unlock(&cdev->cosm_mutex);
	return ret;
}