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
struct max1619_data {int valid; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void** temp; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MAX1619_REG_R_CONFIG ; 
 int /*<<< orphan*/  MAX1619_REG_R_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct max1619_data* dev_get_drvdata (struct device*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * regs_read ; 
 int t_num_regs ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct max1619_data *max1619_update_device(struct device *dev)
{
	struct max1619_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int config, i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ * 2) || !data->valid) {
		dev_dbg(&client->dev, "Updating max1619 data.\n");
		for (i = 0; i < t_num_regs; i++)
			data->temp[i] = i2c_smbus_read_byte_data(client,
					regs_read[i]);
		data->alarms = i2c_smbus_read_byte_data(client,
					MAX1619_REG_R_STATUS);
		/* If OVERT polarity is low, reverse alarm bit */
		config = i2c_smbus_read_byte_data(client, MAX1619_REG_R_CONFIG);
		if (!(config & 0x20))
			data->alarms ^= 0x02;

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}