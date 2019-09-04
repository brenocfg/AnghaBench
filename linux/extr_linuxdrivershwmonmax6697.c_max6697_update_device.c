#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct max6697_data {int valid; int** temp; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; TYPE_1__* chip; int /*<<< orphan*/  update_interval; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int channels; int have_ext; int have_crit; } ;

/* Variables and functions */
 struct max6697_data* ERR_PTR (int) ; 
 int /*<<< orphan*/ * MAX6697_REG_CRIT ; 
 int /*<<< orphan*/ * MAX6697_REG_MAX ; 
 int /*<<< orphan*/  MAX6697_REG_STAT (int) ; 
 int /*<<< orphan*/ * MAX6697_REG_TEMP ; 
 int /*<<< orphan*/ * MAX6697_REG_TEMP_EXT ; 
 size_t MAX6697_TEMP_CRIT ; 
 size_t MAX6697_TEMP_EXT ; 
 size_t MAX6697_TEMP_INPUT ; 
 size_t MAX6697_TEMP_MAX ; 
 struct max6697_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct max6697_data *max6697_update_device(struct device *dev)
{
	struct max6697_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct max6697_data *ret = data;
	int val;
	int i;
	u32 alarms;

	mutex_lock(&data->update_lock);

	if (data->valid &&
	    !time_after(jiffies, data->last_updated
			+ msecs_to_jiffies(data->update_interval)))
		goto abort;

	for (i = 0; i < data->chip->channels; i++) {
		if (data->chip->have_ext & (1 << i)) {
			val = i2c_smbus_read_byte_data(client,
						       MAX6697_REG_TEMP_EXT[i]);
			if (unlikely(val < 0)) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->temp[i][MAX6697_TEMP_EXT] = val;
		}

		val = i2c_smbus_read_byte_data(client, MAX6697_REG_TEMP[i]);
		if (unlikely(val < 0)) {
			ret = ERR_PTR(val);
			goto abort;
		}
		data->temp[i][MAX6697_TEMP_INPUT] = val;

		val = i2c_smbus_read_byte_data(client, MAX6697_REG_MAX[i]);
		if (unlikely(val < 0)) {
			ret = ERR_PTR(val);
			goto abort;
		}
		data->temp[i][MAX6697_TEMP_MAX] = val;

		if (data->chip->have_crit & (1 << i)) {
			val = i2c_smbus_read_byte_data(client,
						       MAX6697_REG_CRIT[i]);
			if (unlikely(val < 0)) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->temp[i][MAX6697_TEMP_CRIT] = val;
		}
	}

	alarms = 0;
	for (i = 0; i < 3; i++) {
		val = i2c_smbus_read_byte_data(client, MAX6697_REG_STAT(i));
		if (unlikely(val < 0)) {
			ret = ERR_PTR(val);
			goto abort;
		}
		alarms = (alarms << 8) | val;
	}
	data->alarms = alarms;
	data->last_updated = jiffies;
	data->valid = true;
abort:
	mutex_unlock(&data->update_lock);

	return ret;
}