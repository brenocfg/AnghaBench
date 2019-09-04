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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PM_QOS_LATENCY_ANY ; 
 scalar_t__ PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT ; 
 int dev_pm_qos_update_user_latency_tolerance (struct device*,scalar_t__) ; 
 scalar_t__ kstrtos32 (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 

__attribute__((used)) static ssize_t pm_qos_latency_tolerance_us_store(struct device *dev,
						 struct device_attribute *attr,
						 const char *buf, size_t n)
{
	s32 value;
	int ret;

	if (kstrtos32(buf, 0, &value) == 0) {
		/* Users can't write negative values directly */
		if (value < 0)
			return -EINVAL;
	} else {
		if (sysfs_streq(buf, "auto"))
			value = PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT;
		else if (sysfs_streq(buf, "any"))
			value = PM_QOS_LATENCY_ANY;
		else
			return -EINVAL;
	}
	ret = dev_pm_qos_update_user_latency_tolerance(dev, value);
	return ret < 0 ? ret : n;
}