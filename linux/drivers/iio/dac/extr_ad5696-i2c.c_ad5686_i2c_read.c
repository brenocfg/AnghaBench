#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct i2c_msg {int flags; int len; char* buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int flags; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct ad5686_state {TYPE_1__* data; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {char* d8; int /*<<< orphan*/  d16; int /*<<< orphan*/  d32; } ;

/* Variables and functions */
 int AD5686_ADDR (int /*<<< orphan*/ ) ; 
 int AD5686_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD5686_CMD_NOOP ; 
 int I2C_M_RD ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5686_i2c_read(struct ad5686_state *st, u8 addr)
{
	struct i2c_client *i2c = to_i2c_client(st->dev);
	struct i2c_msg msg[2] = {
		{
			.addr = i2c->addr,
			.flags = i2c->flags,
			.len = 3,
			.buf = &st->data[0].d8[1],
		},
		{
			.addr = i2c->addr,
			.flags = i2c->flags | I2C_M_RD,
			.len = 2,
			.buf = (char *)&st->data[0].d16,
		},
	};
	int ret;

	st->data[0].d32 = cpu_to_be32(AD5686_CMD(AD5686_CMD_NOOP) |
				      AD5686_ADDR(addr) |
				      0x00);

	ret = i2c_transfer(i2c->adapter, msg, 2);
	if (ret < 0)
		return ret;

	return be16_to_cpu(st->data[0].d16);
}