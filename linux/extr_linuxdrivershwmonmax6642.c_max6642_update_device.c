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
typedef  int u16 ;
struct max6642_data {int valid; int* temp_input; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void* alarms; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  MAX6642_REG_R_LOCAL_TEMP ; 
 int /*<<< orphan*/  MAX6642_REG_R_LOCAL_TEMPL ; 
 int /*<<< orphan*/  MAX6642_REG_R_REMOTE_TEMP ; 
 int /*<<< orphan*/  MAX6642_REG_R_REMOTE_TEMPL ; 
 int /*<<< orphan*/  MAX6642_REG_R_STATUS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct max6642_data* dev_get_drvdata (struct device*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct max6642_data *max6642_update_device(struct device *dev)
{
	struct max6642_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u16 val, tmp;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		dev_dbg(dev, "Updating max6642 data.\n");
		val = i2c_smbus_read_byte_data(client,
					MAX6642_REG_R_LOCAL_TEMPL);
		tmp = (val >> 6) & 3;
		val = i2c_smbus_read_byte_data(client,
					MAX6642_REG_R_LOCAL_TEMP);
		val = (val << 2) | tmp;
		data->temp_input[0] = val;
		val = i2c_smbus_read_byte_data(client,
					MAX6642_REG_R_REMOTE_TEMPL);
		tmp = (val >> 6) & 3;
		val = i2c_smbus_read_byte_data(client,
					MAX6642_REG_R_REMOTE_TEMP);
		val = (val << 2) | tmp;
		data->temp_input[1] = val;
		data->alarms = i2c_smbus_read_byte_data(client,
					MAX6642_REG_R_STATUS);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}