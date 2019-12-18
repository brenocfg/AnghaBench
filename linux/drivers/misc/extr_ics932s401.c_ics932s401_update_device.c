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
struct ics932s401_data {unsigned long sensors_last_updated; int sensors_valid; int* regs; int /*<<< orphan*/  lock; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int NUM_MIRRORED_REGS ; 
 scalar_t__ SENSOR_REFRESH_INTERVAL ; 
 struct ics932s401_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,size_t) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t* regs_to_copy ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct ics932s401_data *ics932s401_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ics932s401_data *data = i2c_get_clientdata(client);
	unsigned long local_jiffies = jiffies;
	int i, temp;

	mutex_lock(&data->lock);
	if (time_before(local_jiffies, data->sensors_last_updated +
		SENSOR_REFRESH_INTERVAL)
		&& data->sensors_valid)
		goto out;

	/*
	 * Each register must be read as a word and then right shifted 8 bits.
	 * Not really sure why this is; setting the "byte count programming"
	 * register to 1 does not fix this problem.
	 */
	for (i = 0; i < NUM_MIRRORED_REGS; i++) {
		temp = i2c_smbus_read_word_data(client, regs_to_copy[i]);
		if (temp < 0)
			data->regs[regs_to_copy[i]] = 0;
		data->regs[regs_to_copy[i]] = temp >> 8;
	}

	data->sensors_last_updated = local_jiffies;
	data->sensors_valid = 1;

out:
	mutex_unlock(&data->lock);
	return data;
}