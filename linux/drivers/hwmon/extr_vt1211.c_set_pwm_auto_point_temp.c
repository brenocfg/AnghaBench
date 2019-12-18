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
struct vt1211_data {int* pwm_ctl; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * pwm_auto_temp; } ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEMP_TO_REG (int,long) ; 
 int /*<<< orphan*/  VT1211_REG_PWM_AUTO_TEMP (int) ; 
 int /*<<< orphan*/  VT1211_REG_PWM_CTL ; 
 struct vt1211_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int vt1211_read8 (struct vt1211_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt1211_write8 (struct vt1211_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t set_pwm_auto_point_temp(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	struct vt1211_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int ap = sensor_attr_2->nr;
	int reg;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;


	mutex_lock(&data->update_lock);

	/* sync the data cache */
	reg = vt1211_read8(data, VT1211_REG_PWM_CTL);
	data->pwm_ctl[0] = reg & 0xf;
	data->pwm_ctl[1] = (reg >> 4) & 0xf;

	data->pwm_auto_temp[ap] = TEMP_TO_REG(data->pwm_ctl[ix] & 7, val);
	vt1211_write8(data, VT1211_REG_PWM_AUTO_TEMP(ap),
		      data->pwm_auto_temp[ap]);
	mutex_unlock(&data->update_lock);

	return count;
}