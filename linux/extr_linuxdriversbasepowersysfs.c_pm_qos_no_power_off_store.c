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
 int EINVAL ; 
 int /*<<< orphan*/  PM_QOS_FLAG_NO_POWER_OFF ; 
 int dev_pm_qos_update_flags (struct device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t pm_qos_no_power_off_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t n)
{
	int ret;

	if (kstrtoint(buf, 0, &ret))
		return -EINVAL;

	if (ret != 0 && ret != 1)
		return -EINVAL;

	ret = dev_pm_qos_update_flags(dev, PM_QOS_FLAG_NO_POWER_OFF, ret);
	return ret < 0 ? ret : n;
}