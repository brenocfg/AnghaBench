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
struct stk8312_data {int range; int mode; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int STK8312_MODE_STANDBY ; 
 int /*<<< orphan*/  STK8312_REG_STH ; 
 int STK8312_RNG_MASK ; 
 int STK8312_RNG_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int stk8312_set_mode (struct stk8312_data*,int) ; 

__attribute__((used)) static int stk8312_set_range(struct stk8312_data *data, u8 range)
{
	int ret;
	u8 masked_reg;
	u8 mode;
	struct i2c_client *client = data->client;

	if (range != 1 && range != 2)
		return -EINVAL;
	else if (range == data->range)
		return 0;

	mode = data->mode;
	/* We need to go in standby mode to modify registers */
	ret = stk8312_set_mode(data, STK8312_MODE_STANDBY);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_read_byte_data(client, STK8312_REG_STH);
	if (ret < 0)
		goto err_activate;

	masked_reg = ret & (~STK8312_RNG_MASK);
	masked_reg |= range << STK8312_RNG_SHIFT;

	ret = i2c_smbus_write_byte_data(client, STK8312_REG_STH, masked_reg);
	if (ret < 0)
		goto err_activate;

	data->range = range;

	return stk8312_set_mode(data, mode);

err_activate:
	dev_err(&client->dev, "failed to change sensor range\n");
	stk8312_set_mode(data, mode);

	return ret;
}