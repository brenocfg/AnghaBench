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
struct it87_data {int fan_ctl; int extra; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  IT87_REG_FAN_CTL ; 
 int /*<<< orphan*/  IT87_REG_TEMP_EXTRA ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct it87_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ has_newer_autopwm (struct it87_data*) ; 
 int it87_read_value (struct it87_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  it87_write_value (struct it87_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* pwm_freq ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm_freq(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	struct it87_data *data = dev_get_drvdata(dev);
	int nr = sensor_attr->index;
	unsigned long val;
	int i;

	if (kstrtoul(buf, 10, &val) < 0)
		return -EINVAL;

	val = clamp_val(val, 0, 1000000);
	val *= has_newer_autopwm(data) ? 256 : 128;

	/* Search for the nearest available frequency */
	for (i = 0; i < 7; i++) {
		if (val > (pwm_freq[i] + pwm_freq[i + 1]) / 2)
			break;
	}

	mutex_lock(&data->update_lock);
	if (nr == 0) {
		data->fan_ctl = it87_read_value(data, IT87_REG_FAN_CTL) & 0x8f;
		data->fan_ctl |= i << 4;
		it87_write_value(data, IT87_REG_FAN_CTL, data->fan_ctl);
	} else {
		data->extra = it87_read_value(data, IT87_REG_TEMP_EXTRA) & 0x8f;
		data->extra |= i << 4;
		it87_write_value(data, IT87_REG_TEMP_EXTRA, data->extra);
	}
	mutex_unlock(&data->update_lock);

	return count;
}