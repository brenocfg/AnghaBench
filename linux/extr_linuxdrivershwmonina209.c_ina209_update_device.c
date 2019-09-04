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
struct ina209_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; scalar_t__* regs; scalar_t__ update_interval; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 struct ina209_data* ERR_PTR (scalar_t__) ; 
 struct ina209_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_smbus_read_word_swapped (struct i2c_client*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct ina209_data *ina209_update_device(struct device *dev)
{
	struct ina209_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct ina209_data *ret = data;
	s32 val;
	int i;

	mutex_lock(&data->update_lock);

	if (!data->valid ||
	    time_after(jiffies, data->last_updated + data->update_interval)) {
		for (i = 0; i < ARRAY_SIZE(data->regs); i++) {
			val = i2c_smbus_read_word_swapped(client, i);
			if (val < 0) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->regs[i] = val;
		}
		data->last_updated = jiffies;
		data->valid = true;
	}
abort:
	mutex_unlock(&data->update_lock);
	return ret;
}