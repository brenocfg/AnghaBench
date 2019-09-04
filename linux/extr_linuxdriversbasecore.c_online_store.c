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
typedef  int ssize_t ;

/* Variables and functions */
 int device_offline (struct device*) ; 
 int device_online (struct device*) ; 
 int lock_device_hotplug_sysfs () ; 
 int strtobool (char const*,int*) ; 
 int /*<<< orphan*/  unlock_device_hotplug () ; 

__attribute__((used)) static ssize_t online_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	bool val;
	int ret;

	ret = strtobool(buf, &val);
	if (ret < 0)
		return ret;

	ret = lock_device_hotplug_sysfs();
	if (ret)
		return ret;

	ret = val ? device_online(dev) : device_offline(dev);
	unlock_device_hotplug();
	return ret < 0 ? ret : count;
}