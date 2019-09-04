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
struct sensor_device_attribute_2 {int nr; int index; } ;
struct it87_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ ** auto_pwm; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int IT87_REG_AUTO_PWM (int,int) ; 
 int IT87_REG_AUTO_TEMP (int,int) ; 
 struct it87_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ has_newer_autopwm (struct it87_data*) ; 
 int /*<<< orphan*/  it87_write_value (struct it87_data*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_to_reg (struct it87_data*,long) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_auto_pwm(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct it87_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sensor_attr =
			to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int point = sensor_attr->index;
	int regaddr;
	long val;

	if (kstrtol(buf, 10, &val) < 0 || val < 0 || val > 255)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->auto_pwm[nr][point] = pwm_to_reg(data, val);
	if (has_newer_autopwm(data))
		regaddr = IT87_REG_AUTO_TEMP(nr, 3);
	else
		regaddr = IT87_REG_AUTO_PWM(nr, point);
	it87_write_value(data, regaddr, data->auto_pwm[nr][point]);
	mutex_unlock(&data->update_lock);
	return count;
}