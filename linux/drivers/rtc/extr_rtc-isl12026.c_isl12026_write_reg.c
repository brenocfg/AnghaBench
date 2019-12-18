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
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  op ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ISL12026_NVMEM_WRITE_TIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int isl12026_arm_write (struct i2c_client*) ; 
 int isl12026_disarm_write (struct i2c_client*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isl12026_write_reg(struct i2c_client *client, int reg, u8 val)
{
	int ret;
	u8 op[3] = {0, reg, val};
	struct i2c_msg msg = {
		.addr	= client->addr,
		.flags	= 0,
		.len	= sizeof(op),
		.buf	= op
	};

	ret = isl12026_arm_write(client);
	if (ret)
		return ret;

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret != 1) {
		dev_err(&client->dev, "write error CCR, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		goto out;
	}

	msleep(ISL12026_NVMEM_WRITE_TIME);

	ret = isl12026_disarm_write(client);
out:
	return ret;
}