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
struct mipid02_dev {struct i2c_client* i2c_client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPID02_CLK_LANE_REG1 ; 
 int /*<<< orphan*/  MIPID02_DATA_LANE0_REG1 ; 
 int /*<<< orphan*/  MIPID02_DATA_LANE1_REG1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mipid02_write_reg (struct mipid02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mipid02_stream_disable(struct mipid02_dev *bridge)
{
	struct i2c_client *client = bridge->i2c_client;
	int ret;

	/* Disable all lanes */
	ret = mipid02_write_reg(bridge, MIPID02_CLK_LANE_REG1, 0);
	if (ret)
		goto error;
	ret = mipid02_write_reg(bridge, MIPID02_DATA_LANE0_REG1, 0);
	if (ret)
		goto error;
	ret = mipid02_write_reg(bridge, MIPID02_DATA_LANE1_REG1, 0);
	if (ret)
		goto error;
error:
	if (ret)
		dev_err(&client->dev, "failed to stream off %d", ret);

	return ret;
}