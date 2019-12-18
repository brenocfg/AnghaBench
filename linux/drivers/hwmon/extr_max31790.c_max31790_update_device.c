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
struct max31790_data {int valid; int fault_status; int* tach; int* fan_config; int* pwm; int* target_count; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct max31790_data* ERR_PTR (int) ; 
 scalar_t__ HZ ; 
 int MAX31790_FAN_CFG_TACH_INPUT ; 
 int /*<<< orphan*/  MAX31790_REG_FAN_FAULT_STATUS1 ; 
 int /*<<< orphan*/  MAX31790_REG_FAN_FAULT_STATUS2 ; 
 int /*<<< orphan*/  MAX31790_REG_PWMOUT (int) ; 
 int /*<<< orphan*/  MAX31790_REG_TACH_COUNT (int) ; 
 int /*<<< orphan*/  MAX31790_REG_TARGET_COUNT (int) ; 
 int NR_CHANNEL ; 
 struct max31790_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct max31790_data *max31790_update_device(struct device *dev)
{
	struct max31790_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct max31790_data *ret = data;
	int i;
	int rv;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		rv = i2c_smbus_read_byte_data(client,
				MAX31790_REG_FAN_FAULT_STATUS1);
		if (rv < 0)
			goto abort;
		data->fault_status = rv & 0x3F;

		rv = i2c_smbus_read_byte_data(client,
				MAX31790_REG_FAN_FAULT_STATUS2);
		if (rv < 0)
			goto abort;
		data->fault_status |= (rv & 0x3F) << 6;

		for (i = 0; i < NR_CHANNEL; i++) {
			rv = i2c_smbus_read_word_swapped(client,
					MAX31790_REG_TACH_COUNT(i));
			if (rv < 0)
				goto abort;
			data->tach[i] = rv;

			if (data->fan_config[i]
			    & MAX31790_FAN_CFG_TACH_INPUT) {
				rv = i2c_smbus_read_word_swapped(client,
					MAX31790_REG_TACH_COUNT(NR_CHANNEL
								+ i));
				if (rv < 0)
					goto abort;
				data->tach[NR_CHANNEL + i] = rv;
			} else {
				rv = i2c_smbus_read_word_swapped(client,
						MAX31790_REG_PWMOUT(i));
				if (rv < 0)
					goto abort;
				data->pwm[i] = rv;

				rv = i2c_smbus_read_word_swapped(client,
						MAX31790_REG_TARGET_COUNT(i));
				if (rv < 0)
					goto abort;
				data->target_count[i] = rv;
			}
		}

		data->last_updated = jiffies;
		data->valid = true;
	}
	goto done;

abort:
	data->valid = false;
	ret = ERR_PTR(rv);

done:
	mutex_unlock(&data->update_lock);

	return ret;
}