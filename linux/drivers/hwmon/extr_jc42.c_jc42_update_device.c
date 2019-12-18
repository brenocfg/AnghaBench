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
struct jc42_data {int valid; int* temp; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct jc42_data* ERR_PTR (int) ; 
 scalar_t__ HZ ; 
 struct jc42_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int t_num_temp ; 
 int /*<<< orphan*/ * temp_regs ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct jc42_data *jc42_update_device(struct device *dev)
{
	struct jc42_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct jc42_data *ret = data;
	int i, val;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		for (i = 0; i < t_num_temp; i++) {
			val = i2c_smbus_read_word_swapped(client, temp_regs[i]);
			if (val < 0) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->temp[i] = val;
		}
		data->last_updated = jiffies;
		data->valid = true;
	}
abort:
	mutex_unlock(&data->update_lock);
	return ret;
}