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
struct tmp421_data {int valid; int config; int channels; int* temp; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  TMP421_CONFIG_REG_1 ; 
 int /*<<< orphan*/ * TMP421_TEMP_LSB ; 
 int /*<<< orphan*/ * TMP421_TEMP_MSB ; 
 struct tmp421_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct tmp421_data *tmp421_update_device(struct device *dev)
{
	struct tmp421_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + 2 * HZ) || !data->valid) {
		data->config = i2c_smbus_read_byte_data(client,
			TMP421_CONFIG_REG_1);

		for (i = 0; i < data->channels; i++) {
			data->temp[i] = i2c_smbus_read_byte_data(client,
				TMP421_TEMP_MSB[i]) << 8;
			data->temp[i] |= i2c_smbus_read_byte_data(client,
				TMP421_TEMP_LSB[i]);
		}
		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}