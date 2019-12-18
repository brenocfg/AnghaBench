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
typedef  int u16 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  reg_buf ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int IQS5XX_NUM_RETRIES ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iqs5xx_read_burst(struct i2c_client *client,
			     u16 reg, void *val, u16 len)
{
	__be16 reg_buf = cpu_to_be16(reg);
	int ret, i;
	struct i2c_msg msg[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.len = sizeof(reg_buf),
			.buf = (u8 *)&reg_buf,
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = (u8 *)val,
		},
	};

	/*
	 * The first addressing attempt outside of a communication window fails
	 * and must be retried, after which the device clock stretches until it
	 * is available.
	 */
	for (i = 0; i < IQS5XX_NUM_RETRIES; i++) {
		ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
		if (ret == ARRAY_SIZE(msg))
			return 0;

		usleep_range(200, 300);
	}

	if (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "Failed to read from address 0x%04X: %d\n",
		reg, ret);

	return ret;
}