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
typedef  int u16 ;
struct w83627ehf_sio_data {scalar_t__ kind; } ;
struct w83627ehf_data {unsigned long* pwm_mode; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int* W83627EHF_PWM_MODE_SHIFT ; 
 int /*<<< orphan*/ * W83627EHF_REG_PWM_ENABLE ; 
 struct w83627ehf_data* dev_get_drvdata (struct device*) ; 
 struct w83627ehf_sio_data* dev_get_platdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nct6776 ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 int w83627ehf_read_value (struct w83627ehf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627ehf_write_value (struct w83627ehf_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_pwm_mode(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct w83627ehf_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	struct w83627ehf_sio_data *sio_data = dev_get_platdata(dev);
	int nr = sensor_attr->index;
	unsigned long val;
	int err;
	u16 reg;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;

	if (val > 1)
		return -EINVAL;

	/* On NCT67766F, DC mode is only supported for pwm1 */
	if (sio_data->kind == nct6776 && nr && val != 1)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	reg = w83627ehf_read_value(data, W83627EHF_REG_PWM_ENABLE[nr]);
	data->pwm_mode[nr] = val;
	reg &= ~(1 << W83627EHF_PWM_MODE_SHIFT[nr]);
	if (!val)
		reg |= 1 << W83627EHF_PWM_MODE_SHIFT[nr];
	w83627ehf_write_value(data, W83627EHF_REG_PWM_ENABLE[nr], reg);
	mutex_unlock(&data->update_lock);
	return count;
}