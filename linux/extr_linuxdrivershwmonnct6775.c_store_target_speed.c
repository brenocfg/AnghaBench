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
typedef  int /*<<< orphan*/  u16 ;
struct sensor_device_attribute {int index; } ;
struct nct6775_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * target_speed; int /*<<< orphan*/ * fan_div; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,unsigned int) ; 
 struct nct6775_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fan_to_reg (unsigned long,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_update_registers (struct nct6775_data*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
store_target_speed(struct device *dev, struct device_attribute *attr,
		   const char *buf, size_t count)
{
	struct nct6775_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	int nr = sattr->index;
	unsigned long val;
	int err;
	u16 speed;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;

	val = clamp_val(val, 0, 1350000U);
	speed = fan_to_reg(val, data->fan_div[nr]);

	mutex_lock(&data->update_lock);
	data->target_speed[nr] = speed;
	pwm_update_registers(data, nr);
	mutex_unlock(&data->update_lock);
	return count;
}