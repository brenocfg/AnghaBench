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
typedef  int u16 ;
struct i2c_msg {int flags; int len; char* buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int flags; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int I2C_M_TEN ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

int i2c_transfer_buffer_flags(const struct i2c_client *client, char *buf,
			      int count, u16 flags)
{
	int ret;
	struct i2c_msg msg = {
		.addr = client->addr,
		.flags = flags | (client->flags & I2C_M_TEN),
		.len = count,
		.buf = buf,
	};

	ret = i2c_transfer(client->adapter, &msg, 1);

	/*
	 * If everything went ok (i.e. 1 msg transferred), return #bytes
	 * transferred, else error code.
	 */
	return (ret == 1) ? count : ret;
}