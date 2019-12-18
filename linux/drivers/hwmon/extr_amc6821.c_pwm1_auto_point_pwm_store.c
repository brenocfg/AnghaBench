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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct amc6821_data {int* pwm1_auto_point_pwm; int /*<<< orphan*/  update_lock; scalar_t__ valid; int /*<<< orphan*/  temp2_auto_point_temp; int /*<<< orphan*/  temp1_auto_point_temp; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMC6821_REG_DCY_LOW_TEMP ; 
 int /*<<< orphan*/  AMC6821_REG_LTEMP_FAN_CTRL ; 
 int /*<<< orphan*/  AMC6821_REG_RTEMP_FAN_CTRL ; 
 size_t EIO ; 
 int clamp_val (long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct amc6821_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ set_slope_register (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pwm1_auto_point_pwm_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	struct amc6821_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int dpwm;
	long val;
	int ret = kstrtol(buf, 10, &val);
	if (ret)
		return ret;

	mutex_lock(&data->update_lock);
	data->pwm1_auto_point_pwm[1] = clamp_val(val, 0, 254);
	if (i2c_smbus_write_byte_data(client, AMC6821_REG_DCY_LOW_TEMP,
			data->pwm1_auto_point_pwm[1])) {
		dev_err(&client->dev, "Register write error, aborting.\n");
		count = -EIO;
		goto EXIT;
	}
	dpwm = data->pwm1_auto_point_pwm[2] - data->pwm1_auto_point_pwm[1];
	if (set_slope_register(client, AMC6821_REG_LTEMP_FAN_CTRL, dpwm,
			data->temp1_auto_point_temp)) {
		count = -EIO;
		goto EXIT;
	}
	if (set_slope_register(client, AMC6821_REG_RTEMP_FAN_CTRL, dpwm,
			data->temp2_auto_point_temp)) {
		count = -EIO;
		goto EXIT;
	}

EXIT:
	data->valid = 0;
	mutex_unlock(&data->update_lock);
	return count;
}