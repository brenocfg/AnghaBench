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
struct tc654_data {int valid; int* rpm_output; int* fan_fault; int config; int status; int duty_cycle; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tc654_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  TC654_REG_CONFIG ; 
 int /*<<< orphan*/  TC654_REG_DUTY_CYCLE ; 
 int /*<<< orphan*/  TC654_REG_FAN_FAULT (int) ; 
 int /*<<< orphan*/  TC654_REG_RPM (int) ; 
 int /*<<< orphan*/  TC654_REG_STATUS ; 
 scalar_t__ TC654_UPDATE_INTERVAL ; 
 struct tc654_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct tc654_data *tc654_update_client(struct device *dev)
{
	struct tc654_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int ret = 0;

	mutex_lock(&data->update_lock);
	if (time_before(jiffies, data->last_updated + TC654_UPDATE_INTERVAL) &&
	    likely(data->valid))
		goto out;

	ret = i2c_smbus_read_byte_data(client, TC654_REG_RPM(0));
	if (ret < 0)
		goto out;
	data->rpm_output[0] = ret;

	ret = i2c_smbus_read_byte_data(client, TC654_REG_RPM(1));
	if (ret < 0)
		goto out;
	data->rpm_output[1] = ret;

	ret = i2c_smbus_read_byte_data(client, TC654_REG_FAN_FAULT(0));
	if (ret < 0)
		goto out;
	data->fan_fault[0] = ret;

	ret = i2c_smbus_read_byte_data(client, TC654_REG_FAN_FAULT(1));
	if (ret < 0)
		goto out;
	data->fan_fault[1] = ret;

	ret = i2c_smbus_read_byte_data(client, TC654_REG_CONFIG);
	if (ret < 0)
		goto out;
	data->config = ret;

	ret = i2c_smbus_read_byte_data(client, TC654_REG_STATUS);
	if (ret < 0)
		goto out;
	data->status = ret;

	ret = i2c_smbus_read_byte_data(client, TC654_REG_DUTY_CYCLE);
	if (ret < 0)
		goto out;
	data->duty_cycle = ret & 0x0f;

	data->last_updated = jiffies;
	data->valid = true;
out:
	mutex_unlock(&data->update_lock);

	if (ret < 0)		/* upon error, encode it in return value */
		data = ERR_PTR(ret);

	return data;
}