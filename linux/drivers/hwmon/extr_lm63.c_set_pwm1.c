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
typedef  int /*<<< orphan*/  u8 ;
struct sensor_device_attribute {int index; } ;
struct lm63_data {int config_fan; unsigned long* pwm1; unsigned long pwm1_freq; int /*<<< orphan*/  update_lock; scalar_t__ pwm_highres; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  LM63_REG_LUT_PWM (int) ; 
 int /*<<< orphan*/  LM63_REG_PWM_VALUE ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct lm63_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,unsigned long) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm1(struct device *dev, struct device_attribute *devattr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct lm63_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int nr = attr->index;
	unsigned long val;
	int err;
	u8 reg;

	if (!(data->config_fan & 0x20)) /* register is read-only */
		return -EPERM;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	reg = nr ? LM63_REG_LUT_PWM(nr - 1) : LM63_REG_PWM_VALUE;
	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	data->pwm1[nr] = data->pwm_highres ? val :
			(val * data->pwm1_freq * 2 + 127) / 255;
	i2c_smbus_write_byte_data(client, reg, data->pwm1[nr]);
	mutex_unlock(&data->update_lock);
	return count;
}