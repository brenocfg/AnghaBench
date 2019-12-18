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
struct i2c_msg {int flags; int len; int* buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int flags; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int I2C_M_RD ; 
 int ITG3200_REG_TEMP_OUT_H ; 
 int ITG3200_SCAN_ELEMENTS ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int itg3200_read_all_channels(struct i2c_client *i2c, __be16 *buf)
{
	u8 tx = 0x80 | ITG3200_REG_TEMP_OUT_H;
	struct i2c_msg msg[2] = {
		{
			.addr = i2c->addr,
			.flags = i2c->flags,
			.len = 1,
			.buf = &tx,
		},
		{
			.addr = i2c->addr,
			.flags = i2c->flags | I2C_M_RD,
			.len = ITG3200_SCAN_ELEMENTS * sizeof(s16),
			.buf = (char *)&buf,
		},
	};

	return i2c_transfer(i2c->adapter, msg, 2);
}