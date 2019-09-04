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
struct it87_data {int** auto_pwm; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  IT87_REG_AUTO_TEMP (int,int) ; 
 struct it87_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  it87_write_value (struct it87_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_auto_pwm_slope(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct it87_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;
	unsigned long val;

	if (kstrtoul(buf, 10, &val) < 0 || val > 127)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->auto_pwm[nr][1] = (data->auto_pwm[nr][1] & 0x80) | val;
	it87_write_value(data, IT87_REG_AUTO_TEMP(nr, 4),
			 data->auto_pwm[nr][1]);
	mutex_unlock(&data->update_lock);
	return count;
}