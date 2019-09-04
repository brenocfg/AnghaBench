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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct amc6821_data {int valid; int stat1; int stat2; int pwm1; int* fan; int fan1_div; int* pwm1_auto_point_pwm; int* temp1_auto_point_temp; int* temp2_auto_point_temp; int pwm1_auto_channels_temp; int pwm1_enable; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; scalar_t__* temp; struct i2c_client* client; } ;
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 int AMC6821_CONF4_PSPR ; 
 int /*<<< orphan*/  AMC6821_REG_CONF1 ; 
 int /*<<< orphan*/  AMC6821_REG_CONF4 ; 
 int /*<<< orphan*/  AMC6821_REG_DCY ; 
 int /*<<< orphan*/  AMC6821_REG_DCY_LOW_TEMP ; 
 int /*<<< orphan*/  AMC6821_REG_LTEMP_FAN_CTRL ; 
 int /*<<< orphan*/  AMC6821_REG_PSV_TEMP ; 
 int /*<<< orphan*/  AMC6821_REG_RTEMP_FAN_CTRL ; 
 int /*<<< orphan*/  AMC6821_REG_STAT1 ; 
 int /*<<< orphan*/  AMC6821_REG_STAT2 ; 
 int FAN1_IDX_LEN ; 
 int HZ ; 
 int TEMP_IDX_LEN ; 
 struct amc6821_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * fan_reg_hi ; 
 int /*<<< orphan*/ * fan_reg_low ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * temp_reg ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct amc6821_data *amc6821_update_device(struct device *dev)
{
	struct amc6821_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int timeout = HZ;
	u8 reg;
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + timeout) ||
			!data->valid) {

		for (i = 0; i < TEMP_IDX_LEN; i++)
			data->temp[i] = (int8_t)i2c_smbus_read_byte_data(
				client, temp_reg[i]);

		data->stat1 = i2c_smbus_read_byte_data(client,
			AMC6821_REG_STAT1);
		data->stat2 = i2c_smbus_read_byte_data(client,
			AMC6821_REG_STAT2);

		data->pwm1 = i2c_smbus_read_byte_data(client,
			AMC6821_REG_DCY);
		for (i = 0; i < FAN1_IDX_LEN; i++) {
			data->fan[i] = i2c_smbus_read_byte_data(
					client,
					fan_reg_low[i]);
			data->fan[i] += i2c_smbus_read_byte_data(
					client,
					fan_reg_hi[i]) << 8;
		}
		data->fan1_div = i2c_smbus_read_byte_data(client,
			AMC6821_REG_CONF4);
		data->fan1_div = data->fan1_div & AMC6821_CONF4_PSPR ? 4 : 2;

		data->pwm1_auto_point_pwm[0] = 0;
		data->pwm1_auto_point_pwm[2] = 255;
		data->pwm1_auto_point_pwm[1] = i2c_smbus_read_byte_data(client,
			AMC6821_REG_DCY_LOW_TEMP);

		data->temp1_auto_point_temp[0] =
			i2c_smbus_read_byte_data(client,
					AMC6821_REG_PSV_TEMP);
		data->temp2_auto_point_temp[0] =
				data->temp1_auto_point_temp[0];
		reg = i2c_smbus_read_byte_data(client,
			AMC6821_REG_LTEMP_FAN_CTRL);
		data->temp1_auto_point_temp[1] = (reg & 0xF8) >> 1;
		reg &= 0x07;
		reg = 0x20 >> reg;
		if (reg > 0)
			data->temp1_auto_point_temp[2] =
				data->temp1_auto_point_temp[1] +
				(data->pwm1_auto_point_pwm[2] -
				data->pwm1_auto_point_pwm[1]) / reg;
		else
			data->temp1_auto_point_temp[2] = 255;

		reg = i2c_smbus_read_byte_data(client,
			AMC6821_REG_RTEMP_FAN_CTRL);
		data->temp2_auto_point_temp[1] = (reg & 0xF8) >> 1;
		reg &= 0x07;
		reg = 0x20 >> reg;
		if (reg > 0)
			data->temp2_auto_point_temp[2] =
				data->temp2_auto_point_temp[1] +
				(data->pwm1_auto_point_pwm[2] -
				data->pwm1_auto_point_pwm[1]) / reg;
		else
			data->temp2_auto_point_temp[2] = 255;

		reg = i2c_smbus_read_byte_data(client, AMC6821_REG_CONF1);
		reg = (reg >> 5) & 0x3;
		switch (reg) {
		case 0: /*open loop: software sets pwm1*/
			data->pwm1_auto_channels_temp = 0;
			data->pwm1_enable = 1;
			break;
		case 2: /*closed loop: remote T (temp2)*/
			data->pwm1_auto_channels_temp = 2;
			data->pwm1_enable = 2;
			break;
		case 3: /*closed loop: local and remote T (temp2)*/
			data->pwm1_auto_channels_temp = 3;
			data->pwm1_enable = 3;
			break;
		case 1: /*
			 * semi-open loop: software sets rpm, chip controls
			 * pwm1, currently not implemented
			 */
			data->pwm1_auto_channels_temp = 0;
			data->pwm1_enable = 0;
			break;
		}

		data->last_updated = jiffies;
		data->valid = 1;
	}
	mutex_unlock(&data->update_lock);
	return data;
}