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
struct hwmon_device_attribute {int /*<<< orphan*/  index; int /*<<< orphan*/  attr; int /*<<< orphan*/  type; TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* write ) (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ;} ;

/* Variables and functions */
 int kstrtol (char const*,int,long*) ; 
 int stub1 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 struct hwmon_device_attribute* to_hwmon_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t hwmon_attr_store(struct device *dev,
				struct device_attribute *devattr,
				const char *buf, size_t count)
{
	struct hwmon_device_attribute *hattr = to_hwmon_attr(devattr);
	long val;
	int ret;

	ret = kstrtol(buf, 10, &val);
	if (ret < 0)
		return ret;

	ret = hattr->ops->write(dev, hattr->type, hattr->attr, hattr->index,
				val);
	if (ret < 0)
		return ret;

	return count;
}