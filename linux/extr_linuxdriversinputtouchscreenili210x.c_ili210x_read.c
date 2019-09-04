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
struct i2c_msg {size_t len; void* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int ili210x_read(struct i2c_client *client, void *buf, size_t len)
{
	struct i2c_msg msg = {
		.addr	= client->addr,
		.flags	= I2C_M_RD,
		.len	= len,
		.buf	= buf,
	};

	if (i2c_transfer(client->adapter, &msg, 1) != 1) {
		dev_err(&client->dev, "i2c transfer failed\n");
		return -EIO;
	}

	return 0;
}