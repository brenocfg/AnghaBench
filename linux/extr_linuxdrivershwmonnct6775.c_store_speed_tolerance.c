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
struct nct6775_data {unsigned long* target_speed_tolerance; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  speed_tolerance_limit; int /*<<< orphan*/ * fan_div; int /*<<< orphan*/ * target_speed; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nct6775_data* dev_get_drvdata (struct device*) ; 
 unsigned long fan_from_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fan_to_reg (int,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_update_registers (struct nct6775_data*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
store_speed_tolerance(struct device *dev, struct device_attribute *attr,
		      const char *buf, size_t count)
{
	struct nct6775_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	int nr = sattr->index;
	unsigned long val;
	int err;
	int low, high;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;

	high = fan_from_reg16(data->target_speed[nr],
			      data->fan_div[nr]) + val;
	low = fan_from_reg16(data->target_speed[nr],
			     data->fan_div[nr]) - val;
	if (low <= 0)
		low = 1;
	if (high < low)
		high = low;

	val = (fan_to_reg(low, data->fan_div[nr]) -
	       fan_to_reg(high, data->fan_div[nr])) / 2;

	/* Limit tolerance as needed */
	val = clamp_val(val, 0, data->speed_tolerance_limit);

	mutex_lock(&data->update_lock);
	data->target_speed_tolerance[nr] = val;
	pwm_update_registers(data, nr);
	mutex_unlock(&data->update_lock);
	return count;
}