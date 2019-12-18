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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct amc6821_data {int* temp1_auto_point_temp; int* temp2_auto_point_temp; int* pwm1_auto_point_pwm; int /*<<< orphan*/  update_lock; scalar_t__ valid; struct i2c_client* client; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; int nr; } ;

/* Variables and functions */
 int AMC6821_REG_LTEMP_FAN_CTRL ; 
 int /*<<< orphan*/  AMC6821_REG_PSV_TEMP ; 
 int AMC6821_REG_RTEMP_FAN_CTRL ; 
 int EINVAL ; 
 size_t EIO ; 
 struct amc6821_data* amc6821_update_device (struct device*) ; 
 int clamp_val (long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ set_slope_register (struct i2c_client*,int,int,int*) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_auto_point_temp_store(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t count)
{
	struct amc6821_data *data = amc6821_update_device(dev);
	struct i2c_client *client = data->client;
	int ix = to_sensor_dev_attr_2(attr)->index;
	int nr = to_sensor_dev_attr_2(attr)->nr;
	u8 *ptemp;
	u8 reg;
	int dpwm;
	long val;
	int ret = kstrtol(buf, 10, &val);
	if (ret)
		return ret;

	switch (nr) {
	case 1:
		ptemp = data->temp1_auto_point_temp;
		reg = AMC6821_REG_LTEMP_FAN_CTRL;
		break;
	case 2:
		ptemp = data->temp2_auto_point_temp;
		reg = AMC6821_REG_RTEMP_FAN_CTRL;
		break;
	default:
		dev_dbg(dev, "Unknown attr->nr (%d).\n", nr);
		return -EINVAL;
	}

	mutex_lock(&data->update_lock);
	data->valid = 0;

	switch (ix) {
	case 0:
		ptemp[0] = clamp_val(val / 1000, 0,
				     data->temp1_auto_point_temp[1]);
		ptemp[0] = clamp_val(ptemp[0], 0,
				     data->temp2_auto_point_temp[1]);
		ptemp[0] = clamp_val(ptemp[0], 0, 63);
		if (i2c_smbus_write_byte_data(
					client,
					AMC6821_REG_PSV_TEMP,
					ptemp[0])) {
				dev_err(&client->dev,
					"Register write error, aborting.\n");
				count = -EIO;
		}
		goto EXIT;
	case 1:
		ptemp[1] = clamp_val(val / 1000, (ptemp[0] & 0x7C) + 4, 124);
		ptemp[1] &= 0x7C;
		ptemp[2] = clamp_val(ptemp[2], ptemp[1] + 1, 255);
		break;
	case 2:
		ptemp[2] = clamp_val(val / 1000, ptemp[1]+1, 255);
		break;
	default:
		dev_dbg(dev, "Unknown attr->index (%d).\n", ix);
		count = -EINVAL;
		goto EXIT;
	}
	dpwm = data->pwm1_auto_point_pwm[2] - data->pwm1_auto_point_pwm[1];
	if (set_slope_register(client, reg, dpwm, ptemp))
		count = -EIO;

EXIT:
	mutex_unlock(&data->update_lock);
	return count;
}