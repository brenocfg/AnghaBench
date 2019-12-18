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
struct max6650_data {int valid; int nr_fans; int* tach; int alarm; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct max6650_data* ERR_PTR (int) ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  MAX6650_REG_ALARM ; 
 struct max6650_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tach_reg ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct max6650_data *max6650_update_device(struct device *dev)
{
	struct max6650_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int reg, err = 0;
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		for (i = 0; i < data->nr_fans; i++) {
			reg = i2c_smbus_read_byte_data(client, tach_reg[i]);
			if (reg < 0) {
				err = reg;
				goto error;
			}
			data->tach[i] = reg;
		}

		/*
		 * Alarms are cleared on read in case the condition that
		 * caused the alarm is removed. Keep the value latched here
		 * for providing the register through different alarm files.
		 */
		reg = i2c_smbus_read_byte_data(client, MAX6650_REG_ALARM);
		if (reg < 0) {
			err = reg;
			goto error;
		}
		data->alarm |= reg;
		data->last_updated = jiffies;
		data->valid = true;
	}

error:
	mutex_unlock(&data->update_lock);
	if (err)
		data = ERR_PTR(err);
	return data;
}