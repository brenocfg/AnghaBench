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
typedef  int u32 ;
struct max31790_data {int* fan_dynamics; int* target_count; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FAN_RPM_MAX ; 
 int FAN_RPM_MIN ; 
 int MAX31790_FAN_DYN_SR_MASK ; 
 int MAX31790_FAN_DYN_SR_SHIFT ; 
 int /*<<< orphan*/  MAX31790_REG_FAN_DYNAMICS (int) ; 
 int /*<<< orphan*/  MAX31790_REG_TARGET_COUNT (int) ; 
 int RPM_TO_REG (long,int) ; 
 int bits_for_tach_period (long) ; 
 void* clamp_val (int,int,int) ; 
 struct max31790_data* dev_get_drvdata (struct device*) ; 
 int get_tach_period (int) ; 
#define  hwmon_fan_target 128 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max31790_write_fan(struct device *dev, u32 attr, int channel,
			      long val)
{
	struct max31790_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int target_count;
	int err = 0;
	u8 bits;
	int sr;

	mutex_lock(&data->update_lock);

	switch (attr) {
	case hwmon_fan_target:
		val = clamp_val(val, FAN_RPM_MIN, FAN_RPM_MAX);
		bits = bits_for_tach_period(val);
		data->fan_dynamics[channel] =
			((data->fan_dynamics[channel] &
			  ~MAX31790_FAN_DYN_SR_MASK) |
			 (bits << MAX31790_FAN_DYN_SR_SHIFT));
		err = i2c_smbus_write_byte_data(client,
					MAX31790_REG_FAN_DYNAMICS(channel),
					data->fan_dynamics[channel]);
		if (err < 0)
			break;

		sr = get_tach_period(data->fan_dynamics[channel]);
		target_count = RPM_TO_REG(val, sr);
		target_count = clamp_val(target_count, 0x1, 0x7FF);

		data->target_count[channel] = target_count << 5;

		err = i2c_smbus_write_word_swapped(client,
					MAX31790_REG_TARGET_COUNT(channel),
					data->target_count[channel]);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	mutex_unlock(&data->update_lock);

	return err;
}