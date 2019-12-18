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
struct sensor_device_attribute {int index; } ;
struct it87_data {int* pwm_ctrl; int* pwm_duty; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 int /*<<< orphan*/ * IT87_REG_PWM ; 
 int /*<<< orphan*/ * IT87_REG_PWM_DUTY ; 
 struct it87_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ has_newer_autopwm (struct it87_data*) ; 
 int /*<<< orphan*/  it87_update_pwm_ctrl (struct it87_data*,int) ; 
 int /*<<< orphan*/  it87_write_value (struct it87_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* pwm_to_reg (struct it87_data*,long) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	struct it87_data *data = dev_get_drvdata(dev);
	int nr = sensor_attr->index;
	long val;

	if (kstrtol(buf, 10, &val) < 0 || val < 0 || val > 255)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	it87_update_pwm_ctrl(data, nr);
	if (has_newer_autopwm(data)) {
		/*
		 * If we are in automatic mode, the PWM duty cycle register
		 * is read-only so we can't write the value.
		 */
		if (data->pwm_ctrl[nr] & 0x80) {
			mutex_unlock(&data->update_lock);
			return -EBUSY;
		}
		data->pwm_duty[nr] = pwm_to_reg(data, val);
		it87_write_value(data, IT87_REG_PWM_DUTY[nr],
				 data->pwm_duty[nr]);
	} else {
		data->pwm_duty[nr] = pwm_to_reg(data, val);
		/*
		 * If we are in manual mode, write the duty cycle immediately;
		 * otherwise, just store it for later use.
		 */
		if (!(data->pwm_ctrl[nr] & 0x80)) {
			data->pwm_ctrl[nr] = data->pwm_duty[nr];
			it87_write_value(data, IT87_REG_PWM[nr],
					 data->pwm_ctrl[nr]);
		}
	}
	mutex_unlock(&data->update_lock);
	return count;
}