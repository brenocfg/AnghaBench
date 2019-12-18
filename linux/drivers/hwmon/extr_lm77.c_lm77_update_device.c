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
struct lm77_data {int valid; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; int /*<<< orphan*/ * temp; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LM77_REG_TEMP ; 
 int /*<<< orphan*/  LM77_TEMP_FROM_REG (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct lm77_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int lm77_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int t_num_temp ; 
 int /*<<< orphan*/ * temp_regs ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct lm77_data *lm77_update_device(struct device *dev)
{
	struct lm77_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) {
		dev_dbg(&client->dev, "Starting lm77 update\n");
		for (i = 0; i < t_num_temp; i++) {
			data->temp[i] =
			  LM77_TEMP_FROM_REG(lm77_read_value(client,
							     temp_regs[i]));
		}
		data->alarms =
			lm77_read_value(client, LM77_REG_TEMP) & 0x0007;
		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}