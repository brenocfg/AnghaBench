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
typedef  unsigned char u32 ;
typedef  int u16 ;
struct i2c_msg {int len; unsigned char* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ET8EK8_REG_16BIT ; 
 int ET8EK8_REG_8BIT ; 
 scalar_t__ I2C_M_RD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int et8ek8_i2c_read_reg(struct i2c_client *client, u16 data_length,
			       u16 reg, u32 *val)
{
	int r;
	struct i2c_msg msg;
	unsigned char data[4];

	if (!client->adapter)
		return -ENODEV;
	if (data_length != ET8EK8_REG_8BIT && data_length != ET8EK8_REG_16BIT)
		return -EINVAL;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 2;
	msg.buf = data;

	/* high byte goes out first */
	data[0] = (u8) (reg >> 8);
	data[1] = (u8) (reg & 0xff);
	r = i2c_transfer(client->adapter, &msg, 1);
	if (r < 0)
		goto err;

	msg.len = data_length;
	msg.flags = I2C_M_RD;
	r = i2c_transfer(client->adapter, &msg, 1);
	if (r < 0)
		goto err;

	*val = 0;
	/* high byte comes first */
	if (data_length == ET8EK8_REG_8BIT)
		*val = data[0];
	else
		*val = (data[1] << 8) + data[0];

	return 0;

err:
	dev_err(&client->dev, "read from offset 0x%x error %d\n", reg, r);

	return r;
}