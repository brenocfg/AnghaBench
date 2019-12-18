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
typedef  int u8 ;
struct stk3310_data {int ps_enabled; int als_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg_state; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int STK3310_STATE_EN_ALS ; 
 int STK3310_STATE_EN_PS ; 
 int STK3310_STATE_STANDBY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stk3310_set_state(struct stk3310_data *data, u8 state)
{
	int ret;
	struct i2c_client *client = data->client;

	/* 3-bit state; 0b100 is not supported. */
	if (state > 7 || state == 4)
		return -EINVAL;

	mutex_lock(&data->lock);
	ret = regmap_field_write(data->reg_state, state);
	if (ret < 0) {
		dev_err(&client->dev, "failed to change sensor state\n");
	} else if (state != STK3310_STATE_STANDBY) {
		/* Don't reset the 'enabled' flags if we're going in standby */
		data->ps_enabled  = !!(state & STK3310_STATE_EN_PS);
		data->als_enabled = !!(state & STK3310_STATE_EN_ALS);
	}
	mutex_unlock(&data->lock);

	return ret;
}