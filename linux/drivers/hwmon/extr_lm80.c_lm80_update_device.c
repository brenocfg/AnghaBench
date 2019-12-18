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
struct lm80_data {int error; int valid; int** in; int** fan; int* temp; int* fan_div; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct lm80_data* ERR_PTR (int) ; 
 int HZ ; 
 int /*<<< orphan*/  LM80_REG_ALARM1 ; 
 int /*<<< orphan*/  LM80_REG_ALARM2 ; 
 int /*<<< orphan*/  LM80_REG_FAN1 ; 
 int /*<<< orphan*/  LM80_REG_FAN2 ; 
 int /*<<< orphan*/  LM80_REG_FANDIV ; 
 int /*<<< orphan*/  LM80_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  LM80_REG_IN (int) ; 
 int /*<<< orphan*/  LM80_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  LM80_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  LM80_REG_RES ; 
 int /*<<< orphan*/  LM80_REG_TEMP ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct lm80_data* dev_get_drvdata (struct device*) ; 
 size_t f_input ; 
 size_t f_min ; 
 size_t i_input ; 
 size_t i_max ; 
 size_t i_min ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lm80_init_client (struct i2c_client*) ; 
 int lm80_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t t_input ; 
 int t_num_temp ; 
 int /*<<< orphan*/ * temp_regs ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct lm80_data *lm80_update_device(struct device *dev)
{
	struct lm80_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int i;
	int rv;
	int prev_rv;
	struct lm80_data *ret = data;

	mutex_lock(&data->update_lock);

	if (data->error)
		lm80_init_client(client);

	if (time_after(jiffies, data->last_updated + 2 * HZ) || !data->valid) {
		dev_dbg(dev, "Starting lm80 update\n");
		for (i = 0; i <= 6; i++) {
			rv = lm80_read_value(client, LM80_REG_IN(i));
			if (rv < 0)
				goto abort;
			data->in[i_input][i] = rv;

			rv = lm80_read_value(client, LM80_REG_IN_MIN(i));
			if (rv < 0)
				goto abort;
			data->in[i_min][i] = rv;

			rv = lm80_read_value(client, LM80_REG_IN_MAX(i));
			if (rv < 0)
				goto abort;
			data->in[i_max][i] = rv;
		}

		rv = lm80_read_value(client, LM80_REG_FAN1);
		if (rv < 0)
			goto abort;
		data->fan[f_input][0] = rv;

		rv = lm80_read_value(client, LM80_REG_FAN_MIN(1));
		if (rv < 0)
			goto abort;
		data->fan[f_min][0] = rv;

		rv = lm80_read_value(client, LM80_REG_FAN2);
		if (rv < 0)
			goto abort;
		data->fan[f_input][1] = rv;

		rv = lm80_read_value(client, LM80_REG_FAN_MIN(2));
		if (rv < 0)
			goto abort;
		data->fan[f_min][1] = rv;

		prev_rv = rv = lm80_read_value(client, LM80_REG_TEMP);
		if (rv < 0)
			goto abort;
		rv = lm80_read_value(client, LM80_REG_RES);
		if (rv < 0)
			goto abort;
		data->temp[t_input] = (prev_rv << 8) | (rv & 0xf0);

		for (i = t_input + 1; i < t_num_temp; i++) {
			rv = lm80_read_value(client, temp_regs[i]);
			if (rv < 0)
				goto abort;
			data->temp[i] = rv << 8;
		}

		rv = lm80_read_value(client, LM80_REG_FANDIV);
		if (rv < 0)
			goto abort;
		data->fan_div[0] = (rv >> 2) & 0x03;
		data->fan_div[1] = (rv >> 4) & 0x03;

		prev_rv = rv = lm80_read_value(client, LM80_REG_ALARM1);
		if (rv < 0)
			goto abort;
		rv = lm80_read_value(client, LM80_REG_ALARM2);
		if (rv < 0)
			goto abort;
		data->alarms = prev_rv + (rv << 8);

		data->last_updated = jiffies;
		data->valid = 1;
		data->error = 0;
	}
	goto done;

abort:
	ret = ERR_PTR(rv);
	data->valid = 0;
	data->error = 1;

done:
	mutex_unlock(&data->update_lock);

	return ret;
}