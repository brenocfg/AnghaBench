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
typedef  int uint8_t ;
struct i2c_msg {int flags; int len; int* buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int I2C_M_NOSTART ; 
 int I2C_M_RD ; 
 int I2C_M_REV_DIR_ADDR ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int as5011_i2c_read(struct i2c_client *client,
			   uint8_t aregaddr, signed char *value)
{
	uint8_t data[2] = { aregaddr };
	struct i2c_msg msg_set[2] = {
		{
			.addr = client->addr,
			.flags = I2C_M_REV_DIR_ADDR,
			.len = 1,
			.buf = (uint8_t *)data
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD | I2C_M_NOSTART,
			.len = 1,
			.buf = (uint8_t *)data
		}
	};
	int error;

	error = i2c_transfer(client->adapter, msg_set, 2);
	if (error < 0)
		return error;

	*value = data[0] & 0x80 ? -1 * (1 + ~data[0]) : data[0];
	return 0;
}