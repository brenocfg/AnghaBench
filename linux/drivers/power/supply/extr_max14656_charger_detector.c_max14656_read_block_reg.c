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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max14656_read_block_reg(struct i2c_client *client, u8 reg,
				  u8 length, u8 *val)
{
	int ret;

	ret = i2c_smbus_read_i2c_block_data(client, reg, length, val);
	if (ret < 0) {
		dev_err(&client->dev, "failed to block read reg 0x%x: %d\n",
				reg, ret);
		return ret;
	}

	return 0;
}