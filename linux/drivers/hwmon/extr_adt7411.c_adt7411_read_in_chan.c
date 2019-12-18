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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct adt7411_data {int vref_cached; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7411_REG_EXT_TEMP_AIN14_LSB ; 
 int /*<<< orphan*/  ADT7411_REG_EXT_TEMP_AIN1_MSB ; 
 int ADT7411_REG_IN_HIGH (int) ; 
 int ADT7411_REG_IN_LOW (int) ; 
 int EOPNOTSUPP ; 
 int adt7411_read_10_bit (struct i2c_client*,int,int /*<<< orphan*/ ,int) ; 
 int adt7411_read_in_alarm (struct device*,int,long*) ; 
 int adt7411_update_vref (struct device*) ; 
 struct adt7411_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_in_alarm 131 
#define  hwmon_in_input 130 
#define  hwmon_in_max 129 
#define  hwmon_in_min 128 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adt7411_read_in_chan(struct device *dev, u32 attr, int channel,
				long *val)
{
	struct adt7411_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;

	int ret;
	int reg, lsb_reg, lsb_shift;
	int nr = channel - 1;

	mutex_lock(&data->update_lock);
	ret = adt7411_update_vref(dev);
	if (ret < 0)
		goto exit_unlock;

	switch (attr) {
	case hwmon_in_input:
		lsb_reg = ADT7411_REG_EXT_TEMP_AIN14_LSB + (nr >> 2);
		lsb_shift = 2 * (nr & 0x03);
		ret = adt7411_read_10_bit(client, lsb_reg,
					  ADT7411_REG_EXT_TEMP_AIN1_MSB + nr,
					  lsb_shift);
		if (ret < 0)
			goto exit_unlock;
		*val = ret * data->vref_cached / 1024;
		ret = 0;
		break;
	case hwmon_in_min:
	case hwmon_in_max:
		reg = (attr == hwmon_in_min)
			? ADT7411_REG_IN_LOW(channel)
			: ADT7411_REG_IN_HIGH(channel);
		ret = i2c_smbus_read_byte_data(client, reg);
		if (ret < 0)
			goto exit_unlock;
		*val = ret * data->vref_cached / 256;
		ret = 0;
		break;
	case hwmon_in_alarm:
		ret = adt7411_read_in_alarm(dev, channel, val);
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}
 exit_unlock:
	mutex_unlock(&data->update_lock);
	return ret;
}