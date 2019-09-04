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
typedef  int /*<<< orphan*/  u8 ;
struct stk8312_data {int /*<<< orphan*/  mode; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STK8312_MODE_STANDBY ; 
 int /*<<< orphan*/  STK8312_REG_INTSU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stk8312_set_mode (struct stk8312_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stk8312_set_interrupts(struct stk8312_data *data, u8 int_mask)
{
	int ret;
	u8 mode;
	struct i2c_client *client = data->client;

	mode = data->mode;
	/* We need to go in standby mode to modify registers */
	ret = stk8312_set_mode(data, STK8312_MODE_STANDBY);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(client, STK8312_REG_INTSU, int_mask);
	if (ret < 0) {
		dev_err(&client->dev, "failed to set interrupts\n");
		stk8312_set_mode(data, mode);
		return ret;
	}

	return stk8312_set_mode(data, mode);
}