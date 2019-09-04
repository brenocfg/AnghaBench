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
struct w83627ehf_data {unsigned long* pwm_enable_orig; unsigned long* pwm_enable; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * NCT6775_REG_FAN_MODE ; 
 int* W83627EHF_PWM_ENABLE_SHIFT ; 
 int /*<<< orphan*/ * W83627EHF_REG_PWM_ENABLE ; 
 struct w83627ehf_data* dev_get_drvdata (struct device*) ; 
 struct w83627ehf_sio_data* dev_get_platdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nct6775 ; 
 scalar_t__ nct6776 ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 int w83627ehf_read_value (struct w83627ehf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627ehf_write_value (struct w83627ehf_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_pwm_enable(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct w83627ehf_data *data = dev_get_drvdata(dev);
	struct w83627ehf_sio_data *sio_data = dev_get_platdata(dev);
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;
	unsigned long val;
	int err;
	u16 reg;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;

	if (!val || (val > 4 && val != data->pwm_enable_orig[nr]))
		return -EINVAL;
	/* SmartFan III mode is not supported on NCT6776F */
	if (sio_data->kind == nct6776 && val == 4)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm_enable[nr] = val;
	if (sio_data->kind == nct6775 || sio_data->kind == nct6776) {
		reg = w83627ehf_read_value(data,
					   NCT6775_REG_FAN_MODE[nr]);
		reg &= 0x0f;
		reg |= (val - 1) << 4;
		w83627ehf_write_value(data,
				      NCT6775_REG_FAN_MODE[nr], reg);
	} else {
		reg = w83627ehf_read_value(data, W83627EHF_REG_PWM_ENABLE[nr]);
		reg &= ~(0x03 << W83627EHF_PWM_ENABLE_SHIFT[nr]);
		reg |= (val - 1) << W83627EHF_PWM_ENABLE_SHIFT[nr];
		w83627ehf_write_value(data, W83627EHF_REG_PWM_ENABLE[nr], reg);
	}
	mutex_unlock(&data->update_lock);
	return count;
}