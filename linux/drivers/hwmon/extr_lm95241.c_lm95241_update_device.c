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
struct lm95241_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void* status; void** temp; int /*<<< orphan*/  interval; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LM95241_REG_R_STATUS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct lm95241_data* dev_get_drvdata (struct device*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/ * lm95241_reg_address ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct lm95241_data *lm95241_update_device(struct device *dev)
{
	struct lm95241_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated
		       + msecs_to_jiffies(data->interval)) ||
	    !data->valid) {
		int i;

		dev_dbg(dev, "Updating lm95241 data.\n");
		for (i = 0; i < ARRAY_SIZE(lm95241_reg_address); i++)
			data->temp[i]
			  = i2c_smbus_read_byte_data(client,
						     lm95241_reg_address[i]);

		data->status = i2c_smbus_read_byte_data(client,
							LM95241_REG_R_STATUS);
		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}