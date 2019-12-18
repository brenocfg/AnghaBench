#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct w83l786ng_data {unsigned long* pwm_mode; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int EINVAL ; 
 int* W83L786NG_PWM_MODE_SHIFT ; 
 int /*<<< orphan*/  W83L786NG_REG_FAN_CFG ; 
 struct w83l786ng_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 int w83l786ng_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83l786ng_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_pwm_mode(struct device *dev, struct device_attribute *attr,
	       const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct w83l786ng_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u8 reg;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	if (val > 1)
		return -EINVAL;
	mutex_lock(&data->update_lock);
	data->pwm_mode[nr] = val;
	reg = w83l786ng_read_value(client, W83L786NG_REG_FAN_CFG);
	reg &= ~(1 << W83L786NG_PWM_MODE_SHIFT[nr]);
	if (!val)
		reg |= 1 << W83L786NG_PWM_MODE_SHIFT[nr];
	w83l786ng_write_value(client, W83L786NG_REG_FAN_CFG, reg);
	mutex_unlock(&data->update_lock);
	return count;
}