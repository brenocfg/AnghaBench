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
struct pc87360_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * pwm; int /*<<< orphan*/  fan_conf; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAN_CONFIG_INVERT (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LD_FAN ; 
 int /*<<< orphan*/  NO_BANK ; 
 int /*<<< orphan*/  PC87360_REG_PWM (size_t) ; 
 int /*<<< orphan*/  PWM_TO_REG (long,int /*<<< orphan*/ ) ; 
 struct pc87360_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc87360_write_value (struct pc87360_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pwm_store(struct device *dev, struct device_attribute *devattr,
			 const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct pc87360_data *data = dev_get_drvdata(dev);
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->pwm[attr->index] = PWM_TO_REG(val,
			      FAN_CONFIG_INVERT(data->fan_conf, attr->index));
	pc87360_write_value(data, LD_FAN, NO_BANK, PC87360_REG_PWM(attr->index),
			    data->pwm[attr->index]);
	mutex_unlock(&data->update_lock);
	return count;
}