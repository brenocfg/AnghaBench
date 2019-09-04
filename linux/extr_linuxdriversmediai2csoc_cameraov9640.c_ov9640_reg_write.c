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
typedef  unsigned char u8 ;
struct i2c_msg {int len; unsigned char* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int ov9640_reg_read (struct i2c_client*,unsigned char,unsigned char*) ; 

__attribute__((used)) static int ov9640_reg_write(struct i2c_client *client, u8 reg, u8 val)
{
	int ret;
	u8 _val;
	unsigned char data[2] = { reg, val };
	struct i2c_msg msg = {
		.addr	= client->addr,
		.flags	= 0,
		.len	= 2,
		.buf	= data,
	};

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret < 0) {
		dev_err(&client->dev, "Failed writing register 0x%02x!\n", reg);
		return ret;
	}

	/* we have to read the register back ... no idea why, maybe HW bug */
	ret = ov9640_reg_read(client, reg, &_val);
	if (ret)
		dev_err(&client->dev,
			"Failed reading back register 0x%02x!\n", reg);

	return 0;
}