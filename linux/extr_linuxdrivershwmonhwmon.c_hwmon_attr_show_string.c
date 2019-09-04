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
struct TYPE_2__ {int (* read_string ) (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ;} ;

/* Variables and functions */
 int sprintf (char*,char*,char const*) ; 
 int stub1 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 struct hwmon_device_attribute* to_hwmon_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t hwmon_attr_show_string(struct device *dev,
				      struct device_attribute *devattr,
				      char *buf)
{
	struct hwmon_device_attribute *hattr = to_hwmon_attr(devattr);
	const char *s;
	int ret;

	ret = hattr->ops->read_string(dev, hattr->type, hattr->attr,
				      hattr->index, &s);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%s\n", s);
}