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
typedef  int u32 ;
struct w83781d_data {unsigned long pwm2_enable; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_CONFIG ; 
 int /*<<< orphan*/  W83781D_REG_PWMCLK12 ; 
 struct w83781d_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int w83781d_read_value (struct w83781d_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83781d_write_value (struct w83781d_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
pwm2_enable_store(struct device *dev, struct device_attribute *da,
		const char *buf, size_t count)
{
	struct w83781d_data *data = dev_get_drvdata(dev);
	unsigned long val;
	u32 reg;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);

	switch (val) {
	case 0:
	case 1:
		reg = w83781d_read_value(data, W83781D_REG_PWMCLK12);
		w83781d_write_value(data, W83781D_REG_PWMCLK12,
				    (reg & 0xf7) | (val << 3));

		reg = w83781d_read_value(data, W83781D_REG_BEEP_CONFIG);
		w83781d_write_value(data, W83781D_REG_BEEP_CONFIG,
				    (reg & 0xef) | (!val << 4));

		data->pwm2_enable = val;
		break;

	default:
		mutex_unlock(&data->update_lock);
		return -EINVAL;
	}

	mutex_unlock(&data->update_lock);
	return count;
}