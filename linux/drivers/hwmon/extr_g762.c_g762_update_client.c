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
struct i2c_client {int dummy; } ;
struct g762_data {int valid; int set_cnt; int act_cnt; int fan_sta; int set_out; int fan_cmd1; int fan_cmd2; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct g762_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  G762_REG_ACT_CNT ; 
 int /*<<< orphan*/  G762_REG_FAN_CMD1 ; 
 int /*<<< orphan*/  G762_REG_FAN_CMD2 ; 
 int /*<<< orphan*/  G762_REG_FAN_STA ; 
 int /*<<< orphan*/  G762_REG_SET_CNT ; 
 int /*<<< orphan*/  G762_REG_SET_OUT ; 
 scalar_t__ G762_UPDATE_INTERVAL ; 
 struct g762_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct g762_data *g762_update_client(struct device *dev)
{
	struct g762_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int ret = 0;

	mutex_lock(&data->update_lock);
	if (time_before(jiffies, data->last_updated + G762_UPDATE_INTERVAL) &&
	    likely(data->valid))
		goto out;

	ret = i2c_smbus_read_byte_data(client, G762_REG_SET_CNT);
	if (ret < 0)
		goto out;
	data->set_cnt = ret;

	ret = i2c_smbus_read_byte_data(client, G762_REG_ACT_CNT);
	if (ret < 0)
		goto out;
	data->act_cnt = ret;

	ret = i2c_smbus_read_byte_data(client, G762_REG_FAN_STA);
	if (ret < 0)
		goto out;
	data->fan_sta = ret;

	ret = i2c_smbus_read_byte_data(client, G762_REG_SET_OUT);
	if (ret < 0)
		goto out;
	data->set_out = ret;

	ret = i2c_smbus_read_byte_data(client, G762_REG_FAN_CMD1);
	if (ret < 0)
		goto out;
	data->fan_cmd1 = ret;

	ret = i2c_smbus_read_byte_data(client, G762_REG_FAN_CMD2);
	if (ret < 0)
		goto out;
	data->fan_cmd2 = ret;

	data->last_updated = jiffies;
	data->valid = true;
 out:
	mutex_unlock(&data->update_lock);

	if (ret < 0) /* upon error, encode it in return value */
		data = ERR_PTR(ret);

	return data;
}