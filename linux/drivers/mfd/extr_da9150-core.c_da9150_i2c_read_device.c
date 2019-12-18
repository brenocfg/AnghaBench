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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int da9150_i2c_read_device(struct i2c_client *client, u8 addr, int count,
				  u8 *buf)
{
	struct i2c_msg xfer;
	int ret;

	/*
	 * Read is split into two transfers as device expects STOP/START rather
	 * than repeated start to carry out this kind of access.
	 */

	/* Write address */
	xfer.addr = client->addr;
	xfer.flags = 0;
	xfer.len = 1;
	xfer.buf = &addr;

	ret = i2c_transfer(client->adapter, &xfer, 1);
	if (ret != 1) {
		if (ret < 0)
			return ret;
		else
			return -EIO;
	}

	/* Read data */
	xfer.addr = client->addr;
	xfer.flags = I2C_M_RD;
	xfer.len = count;
	xfer.buf = buf;

	ret = i2c_transfer(client->adapter, &xfer, 1);
	if (ret == 1)
		return 0;
	else if (ret < 0)
		return ret;
	else
		return -EIO;
}