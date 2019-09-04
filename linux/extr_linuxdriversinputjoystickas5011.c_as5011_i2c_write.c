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
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_IGNORE_NAK ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int as5011_i2c_write(struct i2c_client *client,
			    uint8_t aregaddr,
			    uint8_t avalue)
{
	uint8_t data[2] = { aregaddr, avalue };
	struct i2c_msg msg = {
		.addr = client->addr,
		.flags = I2C_M_IGNORE_NAK,
		.len = 2,
		.buf = (uint8_t *)data
	};
	int error;

	error = i2c_transfer(client->adapter, &msg, 1);
	return error < 0 ? error : 0;
}