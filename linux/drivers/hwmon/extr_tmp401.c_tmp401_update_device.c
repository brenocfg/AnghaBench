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
struct tmp401_data {unsigned long last_updated; int valid; scalar_t__ kind; int* status; int config; int temp_crit_hyst; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  update_interval; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 struct tmp401_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  TMP401_CONFIG_READ ; 
 int /*<<< orphan*/  TMP401_STATUS ; 
 int TMP401_STATUS_LOCAL_CRIT ; 
 int TMP401_STATUS_LOCAL_HIGH ; 
 int TMP401_STATUS_LOCAL_LOW ; 
 int TMP401_STATUS_REMOTE_CRIT ; 
 int TMP401_STATUS_REMOTE_HIGH ; 
 int TMP401_STATUS_REMOTE_LOW ; 
 int TMP401_STATUS_REMOTE_OPEN ; 
 int /*<<< orphan*/  TMP401_TEMP_CRIT_HYST ; 
 int /*<<< orphan*/ * TMP432_STATUS_REG ; 
 struct tmp401_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int tmp401_update_device_reg16 (struct i2c_client*,struct tmp401_data*) ; 
 scalar_t__ tmp432 ; 

__attribute__((used)) static struct tmp401_data *tmp401_update_device(struct device *dev)
{
	struct tmp401_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct tmp401_data *ret = data;
	int i, val;
	unsigned long next_update;

	mutex_lock(&data->update_lock);

	next_update = data->last_updated +
		      msecs_to_jiffies(data->update_interval);
	if (time_after(jiffies, next_update) || !data->valid) {
		if (data->kind != tmp432) {
			/*
			 * The driver uses the TMP432 status format internally.
			 * Convert status to TMP432 format for other chips.
			 */
			val = i2c_smbus_read_byte_data(client, TMP401_STATUS);
			if (val < 0) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->status[0] =
			  (val & TMP401_STATUS_REMOTE_OPEN) >> 1;
			data->status[1] =
			  ((val & TMP401_STATUS_REMOTE_LOW) >> 2) |
			  ((val & TMP401_STATUS_LOCAL_LOW) >> 5);
			data->status[2] =
			  ((val & TMP401_STATUS_REMOTE_HIGH) >> 3) |
			  ((val & TMP401_STATUS_LOCAL_HIGH) >> 6);
			data->status[3] = val & (TMP401_STATUS_LOCAL_CRIT
						| TMP401_STATUS_REMOTE_CRIT);
		} else {
			for (i = 0; i < ARRAY_SIZE(data->status); i++) {
				val = i2c_smbus_read_byte_data(client,
							TMP432_STATUS_REG[i]);
				if (val < 0) {
					ret = ERR_PTR(val);
					goto abort;
				}
				data->status[i] = val;
			}
		}

		val = i2c_smbus_read_byte_data(client, TMP401_CONFIG_READ);
		if (val < 0) {
			ret = ERR_PTR(val);
			goto abort;
		}
		data->config = val;
		val = tmp401_update_device_reg16(client, data);
		if (val < 0) {
			ret = ERR_PTR(val);
			goto abort;
		}
		val = i2c_smbus_read_byte_data(client, TMP401_TEMP_CRIT_HYST);
		if (val < 0) {
			ret = ERR_PTR(val);
			goto abort;
		}
		data->temp_crit_hyst = val;

		data->last_updated = jiffies;
		data->valid = 1;
	}

abort:
	mutex_unlock(&data->update_lock);
	return ret;
}