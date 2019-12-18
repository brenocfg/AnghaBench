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
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  long long ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 long long ltc2945_reg_to_val (struct device*,int /*<<< orphan*/ ) ; 
 long long snprintf (char*,int /*<<< orphan*/ ,char*,long long) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ltc2945_value_show(struct device *dev,
				  struct device_attribute *da, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	long long value;

	value = ltc2945_reg_to_val(dev, attr->index);
	if (value < 0)
		return value;
	return snprintf(buf, PAGE_SIZE, "%lld\n", value);
}