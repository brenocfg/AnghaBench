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
struct hwmon_device_attribute {int type; int /*<<< orphan*/  name; scalar_t__ index; int /*<<< orphan*/  attr; TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;
struct TYPE_2__ {int (* read_string ) (struct device*,int,int /*<<< orphan*/ ,scalar_t__,char const**) ;} ;

/* Variables and functions */
 scalar_t__ hwmon_attr_base (int) ; 
 int sprintf (char*,char*,char const*) ; 
 int stub1 (struct device*,int,int /*<<< orphan*/ ,scalar_t__,char const**) ; 
 struct hwmon_device_attribute* to_hwmon_attr (struct device_attribute*) ; 
 int /*<<< orphan*/  trace_hwmon_attr_show_string (scalar_t__,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static ssize_t hwmon_attr_show_string(struct device *dev,
				      struct device_attribute *devattr,
				      char *buf)
{
	struct hwmon_device_attribute *hattr = to_hwmon_attr(devattr);
	enum hwmon_sensor_types type = hattr->type;
	const char *s;
	int ret;

	ret = hattr->ops->read_string(dev, hattr->type, hattr->attr,
				      hattr->index, &s);
	if (ret < 0)
		return ret;

	trace_hwmon_attr_show_string(hattr->index + hwmon_attr_base(type),
				     hattr->name, s);

	return sprintf(buf, "%s\n", s);
}