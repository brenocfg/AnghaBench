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
struct lm95234_data {int valid; int status; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; int /*<<< orphan*/ * temp; scalar_t__ interval; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LM95234_REG_STS_FAULT ; 
 int /*<<< orphan*/  LM95234_REG_STS_TCRIT1 ; 
 int /*<<< orphan*/  LM95234_REG_STS_TCRIT2 ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int lm95234_fill_cache (struct lm95234_data*,struct i2c_client*) ; 
 int lm95234_read_temp (struct i2c_client*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int lm95234_update_device(struct lm95234_data *data)
{
	struct i2c_client *client = data->client;
	int ret;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + data->interval) ||
	    !data->valid) {
		int i;

		if (!data->valid) {
			ret = lm95234_fill_cache(data, client);
			if (ret < 0)
				goto abort;
		}

		data->valid = false;
		for (i = 0; i < ARRAY_SIZE(data->temp); i++) {
			ret = lm95234_read_temp(client, i, &data->temp[i]);
			if (ret < 0)
				goto abort;
		}

		ret = i2c_smbus_read_byte_data(client, LM95234_REG_STS_FAULT);
		if (ret < 0)
			goto abort;
		data->status = ret;

		ret = i2c_smbus_read_byte_data(client, LM95234_REG_STS_TCRIT1);
		if (ret < 0)
			goto abort;
		data->status |= ret << 8;

		ret = i2c_smbus_read_byte_data(client, LM95234_REG_STS_TCRIT2);
		if (ret < 0)
			goto abort;
		data->status |= ret << 16;

		data->last_updated = jiffies;
		data->valid = true;
	}
	ret = 0;
abort:
	mutex_unlock(&data->update_lock);

	return ret;
}