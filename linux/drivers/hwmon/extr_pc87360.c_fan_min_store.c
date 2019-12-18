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
struct pc87360_data {int* fan_status; int* fan; int* fan_min; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAN_DIV_FROM_REG (int) ; 
 long FAN_TO_REG (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_FAN ; 
 int /*<<< orphan*/  NO_BANK ; 
 int /*<<< orphan*/  PC87360_REG_FAN_MIN (size_t) ; 
 int /*<<< orphan*/  PC87360_REG_FAN_STATUS (size_t) ; 
 struct pc87360_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc87360_write_value (struct pc87360_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_min_store(struct device *dev,
			     struct device_attribute *devattr,
			     const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct pc87360_data *data = dev_get_drvdata(dev);
	long fan_min;
	int err;

	err = kstrtol(buf, 10, &fan_min);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	fan_min = FAN_TO_REG(fan_min,
			     FAN_DIV_FROM_REG(data->fan_status[attr->index]));

	/* If it wouldn't fit, change clock divisor */
	while (fan_min > 255
	    && (data->fan_status[attr->index] & 0x60) != 0x60) {
		fan_min >>= 1;
		data->fan[attr->index] >>= 1;
		data->fan_status[attr->index] += 0x20;
	}
	data->fan_min[attr->index] = fan_min > 255 ? 255 : fan_min;
	pc87360_write_value(data, LD_FAN, NO_BANK,
			    PC87360_REG_FAN_MIN(attr->index),
			    data->fan_min[attr->index]);

	/* Write new divider, preserve alarm bits */
	pc87360_write_value(data, LD_FAN, NO_BANK,
			    PC87360_REG_FAN_STATUS(attr->index),
			    data->fan_status[attr->index] & 0xF9);
	mutex_unlock(&data->update_lock);

	return count;
}