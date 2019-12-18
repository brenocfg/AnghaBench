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
struct device {int /*<<< orphan*/  driver; } ;
struct ccwgroup_device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ccwgroup_set_offline (struct ccwgroup_device*) ; 
 int ccwgroup_set_online (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 

__attribute__((used)) static ssize_t ccwgroup_online_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct ccwgroup_device *gdev = to_ccwgroupdev(dev);
	unsigned long value;
	int ret;

	device_lock(dev);
	if (!dev->driver) {
		ret = -EINVAL;
		goto out;
	}

	ret = kstrtoul(buf, 0, &value);
	if (ret)
		goto out;

	if (value == 1)
		ret = ccwgroup_set_online(gdev);
	else if (value == 0)
		ret = ccwgroup_set_offline(gdev);
	else
		ret = -EINVAL;
out:
	device_unlock(dev);
	return (ret == 0) ? count : ret;
}