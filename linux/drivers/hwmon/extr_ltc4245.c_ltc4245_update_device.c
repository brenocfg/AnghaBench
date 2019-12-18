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
struct ltc4245_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; scalar_t__* vregs; scalar_t__* cregs; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ HZ ; 
 struct ltc4245_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ltc4245_update_gpios (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ltc4245_data *ltc4245_update_device(struct device *dev)
{
	struct ltc4245_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	s32 val;
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {

		/* Read control registers -- 0x00 to 0x07 */
		for (i = 0; i < ARRAY_SIZE(data->cregs); i++) {
			val = i2c_smbus_read_byte_data(client, i);
			if (unlikely(val < 0))
				data->cregs[i] = 0;
			else
				data->cregs[i] = val;
		}

		/* Read voltage registers -- 0x10 to 0x1c */
		for (i = 0; i < ARRAY_SIZE(data->vregs); i++) {
			val = i2c_smbus_read_byte_data(client, i+0x10);
			if (unlikely(val < 0))
				data->vregs[i] = 0;
			else
				data->vregs[i] = val;
		}

		/* Update GPIO readings */
		ltc4245_update_gpios(dev);

		data->last_updated = jiffies;
		data->valid = true;
	}

	mutex_unlock(&data->update_lock);

	return data;
}