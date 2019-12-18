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
struct ltc4215_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; scalar_t__* regs; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct ltc4215_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ltc4215_data *ltc4215_update_device(struct device *dev)
{
	struct ltc4215_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	s32 val;
	int i;

	mutex_lock(&data->update_lock);

	/* The chip's A/D updates 10 times per second */
	if (time_after(jiffies, data->last_updated + HZ / 10) || !data->valid) {

		dev_dbg(&client->dev, "Starting ltc4215 update\n");

		/* Read all registers */
		for (i = 0; i < ARRAY_SIZE(data->regs); i++) {
			val = i2c_smbus_read_byte_data(client, i);
			if (unlikely(val < 0))
				data->regs[i] = 0;
			else
				data->regs[i] = val;
		}

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}