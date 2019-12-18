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
struct max6639_data {int valid; int status; int* fan; int* temp; int* temp_fault; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct max6639_data* ERR_PTR (int) ; 
 int HZ ; 
 int /*<<< orphan*/  MAX6639_REG_FAN_CNT (int) ; 
 int /*<<< orphan*/  MAX6639_REG_STATUS ; 
 int /*<<< orphan*/  MAX6639_REG_TEMP (int) ; 
 int /*<<< orphan*/  MAX6639_REG_TEMP_EXT (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct max6639_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct max6639_data *max6639_update_device(struct device *dev)
{
	struct max6639_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct max6639_data *ret = data;
	int i;
	int status_reg;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + 2 * HZ) || !data->valid) {
		int res;

		dev_dbg(&client->dev, "Starting max6639 update\n");

		status_reg = i2c_smbus_read_byte_data(client,
						      MAX6639_REG_STATUS);
		if (status_reg < 0) {
			ret = ERR_PTR(status_reg);
			goto abort;
		}

		data->status = status_reg;

		for (i = 0; i < 2; i++) {
			res = i2c_smbus_read_byte_data(client,
					MAX6639_REG_FAN_CNT(i));
			if (res < 0) {
				ret = ERR_PTR(res);
				goto abort;
			}
			data->fan[i] = res;

			res = i2c_smbus_read_byte_data(client,
					MAX6639_REG_TEMP_EXT(i));
			if (res < 0) {
				ret = ERR_PTR(res);
				goto abort;
			}
			data->temp[i] = res >> 5;
			data->temp_fault[i] = res & 0x01;

			res = i2c_smbus_read_byte_data(client,
					MAX6639_REG_TEMP(i));
			if (res < 0) {
				ret = ERR_PTR(res);
				goto abort;
			}
			data->temp[i] |= res << 3;
		}

		data->last_updated = jiffies;
		data->valid = 1;
	}
abort:
	mutex_unlock(&data->update_lock);

	return ret;
}