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
struct ds620_data {int valid; int* temp; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/ * DS620_REG_TEMP ; 
 struct ds620_data* ERR_PTR (int) ; 
 int HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct ds620_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct ds620_data *ds620_update_client(struct device *dev)
{
	struct ds620_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct ds620_data *ret = data;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) {
		int i;
		int res;

		dev_dbg(&client->dev, "Starting ds620 update\n");

		for (i = 0; i < ARRAY_SIZE(data->temp); i++) {
			res = i2c_smbus_read_word_swapped(client,
							  DS620_REG_TEMP[i]);
			if (res < 0) {
				ret = ERR_PTR(res);
				goto abort;
			}

			data->temp[i] = res;
		}

		data->last_updated = jiffies;
		data->valid = 1;
	}
abort:
	mutex_unlock(&data->update_lock);

	return ret;
}