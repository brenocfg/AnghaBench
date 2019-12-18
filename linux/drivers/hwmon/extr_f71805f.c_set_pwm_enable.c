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
typedef  int u8 ;
struct sensor_device_attribute {int index; } ;
struct f71805f_data {int* fan_ctrl; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  F71805F_REG_FAN_CTRL (int) ; 
 int FAN_CTRL_MODE_MANUAL ; 
 int FAN_CTRL_MODE_MASK ; 
 int FAN_CTRL_MODE_SPEED ; 
 int FAN_CTRL_MODE_TEMPERATURE ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct f71805f_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * f71805f_attr_pwm ; 
 int f71805f_read8 (struct f71805f_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f71805f_write8 (struct f71805f_data*,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sysfs_chmod_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm_enable(struct device *dev, struct device_attribute
			      *devattr, const char *buf, size_t count)
{
	struct f71805f_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	int nr = attr->index;
	u8 reg;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	if (val < 1 || val > 3)
		return -EINVAL;

	if (val > 1) { /* Automatic mode, user can't set PWM value */
		if (sysfs_chmod_file(&dev->kobj, f71805f_attr_pwm[nr],
				     S_IRUGO))
			dev_dbg(dev, "chmod -w pwm%d failed\n", nr + 1);
	}

	mutex_lock(&data->update_lock);
	reg = f71805f_read8(data, F71805F_REG_FAN_CTRL(nr))
	    & ~FAN_CTRL_MODE_MASK;
	switch (val) {
	case 1:
		reg |= FAN_CTRL_MODE_MANUAL;
		break;
	case 2:
		reg |= FAN_CTRL_MODE_TEMPERATURE;
		break;
	case 3:
		reg |= FAN_CTRL_MODE_SPEED;
		break;
	}
	data->fan_ctrl[nr] = reg;
	f71805f_write8(data, F71805F_REG_FAN_CTRL(nr), reg);
	mutex_unlock(&data->update_lock);

	if (val == 1) { /* Manual mode, user can set PWM value */
		if (sysfs_chmod_file(&dev->kobj, f71805f_attr_pwm[nr],
				     S_IRUGO | S_IWUSR))
			dev_dbg(dev, "chmod +w pwm%d failed\n", nr + 1);
	}

	return count;
}