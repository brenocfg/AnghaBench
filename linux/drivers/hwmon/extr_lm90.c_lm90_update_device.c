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
struct lm90_data {int valid; unsigned long last_updated; int* temp8; int* temp11; int alarms; scalar_t__ kind; int config_orig; int alert_alarms; int config; scalar_t__ reg_local_ext; int /*<<< orphan*/  update_interval; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM90_REG_R_LOCAL_HIGH ; 
 int /*<<< orphan*/  LM90_REG_R_LOCAL_LOW ; 
 int /*<<< orphan*/  LM90_REG_R_LOCAL_TEMP ; 
 int /*<<< orphan*/  LM90_REG_R_REMOTE_TEMPH ; 
 scalar_t__ LM90_REG_R_REMOTE_TEMPL ; 
 int /*<<< orphan*/  LM90_REG_R_STATUS ; 
 size_t LOCAL_HIGH ; 
 size_t LOCAL_LOW ; 
 size_t LOCAL_TEMP ; 
 int /*<<< orphan*/  MAX6696_REG_R_STATUS2 ; 
 size_t REMOTE2_TEMP ; 
 size_t REMOTE_TEMP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct lm90_data* dev_get_drvdata (struct device*) ; 
 unsigned long jiffies ; 
 int lm90_read16 (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__) ; 
 int lm90_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int lm90_select_remote_channel (struct lm90_data*,int) ; 
 int /*<<< orphan*/  lm90_update_confreg (struct lm90_data*,int) ; 
 int lm90_update_limits (struct device*) ; 
 scalar_t__ max6696 ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int lm90_update_device(struct device *dev)
{
	struct lm90_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long next_update;
	int val;

	if (!data->valid) {
		val = lm90_update_limits(dev);
		if (val < 0)
			return val;
	}

	next_update = data->last_updated +
		      msecs_to_jiffies(data->update_interval);
	if (time_after(jiffies, next_update) || !data->valid) {
		dev_dbg(&client->dev, "Updating lm90 data.\n");

		data->valid = false;

		val = lm90_read_reg(client, LM90_REG_R_LOCAL_LOW);
		if (val < 0)
			return val;
		data->temp8[LOCAL_LOW] = val;

		val = lm90_read_reg(client, LM90_REG_R_LOCAL_HIGH);
		if (val < 0)
			return val;
		data->temp8[LOCAL_HIGH] = val;

		if (data->reg_local_ext) {
			val = lm90_read16(client, LM90_REG_R_LOCAL_TEMP,
					  data->reg_local_ext);
			if (val < 0)
				return val;
			data->temp11[LOCAL_TEMP] = val;
		} else {
			val = lm90_read_reg(client, LM90_REG_R_LOCAL_TEMP);
			if (val < 0)
				return val;
			data->temp11[LOCAL_TEMP] = val << 8;
		}
		val = lm90_read16(client, LM90_REG_R_REMOTE_TEMPH,
				  LM90_REG_R_REMOTE_TEMPL);
		if (val < 0)
			return val;
		data->temp11[REMOTE_TEMP] = val;

		val = lm90_read_reg(client, LM90_REG_R_STATUS);
		if (val < 0)
			return val;
		data->alarms = val;	/* lower 8 bit of alarms */

		if (data->kind == max6696) {
			val = lm90_select_remote_channel(data, 1);
			if (val < 0)
				return val;

			val = lm90_read16(client, LM90_REG_R_REMOTE_TEMPH,
					  LM90_REG_R_REMOTE_TEMPL);
			if (val < 0) {
				lm90_select_remote_channel(data, 0);
				return val;
			}
			data->temp11[REMOTE2_TEMP] = val;

			lm90_select_remote_channel(data, 0);

			val = lm90_read_reg(client, MAX6696_REG_R_STATUS2);
			if (val < 0)
				return val;
			data->alarms |= val << 8;
		}

		/*
		 * Re-enable ALERT# output if it was originally enabled and
		 * relevant alarms are all clear
		 */
		if (!(data->config_orig & 0x80) &&
		    !(data->alarms & data->alert_alarms)) {
			if (data->config & 0x80) {
				dev_dbg(&client->dev, "Re-enabling ALERT#\n");
				lm90_update_confreg(data, data->config & ~0x80);
			}
		}

		data->last_updated = jiffies;
		data->valid = true;
	}

	return 0;
}