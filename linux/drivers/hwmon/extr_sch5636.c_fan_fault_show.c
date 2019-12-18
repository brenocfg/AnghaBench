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
struct sensor_device_attribute {size_t index; } ;
struct sch5636_data {int* fan_ctrl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sch5636_data*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTR_ERR (struct sch5636_data*) ; 
 int SCH5636_FAN_NOT_PRESENT ; 
 struct sch5636_data* sch5636_update_device (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_fault_show(struct device *dev,
			      struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct sch5636_data *data = sch5636_update_device(dev);
	int val;

	if (IS_ERR(data))
		return PTR_ERR(data);

	val = (data->fan_ctrl[attr->index] & SCH5636_FAN_NOT_PRESENT) ? 1 : 0;
	return snprintf(buf, PAGE_SIZE, "%d\n", val);
}