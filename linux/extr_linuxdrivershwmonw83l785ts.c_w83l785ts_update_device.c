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
struct w83l785ts_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void** temp; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  W83L785TS_REG_TEMP ; 
 int /*<<< orphan*/  W83L785TS_REG_TEMP_OVER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct w83l785ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 void* w83l785ts_read_value (struct i2c_client*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static struct w83l785ts_data *w83l785ts_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct w83l785ts_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (!data->valid || time_after(jiffies, data->last_updated + HZ * 2)) {
		dev_dbg(&client->dev, "Updating w83l785ts data.\n");
		data->temp[0] = w83l785ts_read_value(client,
				W83L785TS_REG_TEMP, data->temp[0]);
		data->temp[1] = w83l785ts_read_value(client,
				W83L785TS_REG_TEMP_OVER, data->temp[1]);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}