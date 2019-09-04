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
typedef  int u8 ;
typedef  int u16 ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;
struct dib3000_state {int /*<<< orphan*/  i2c; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  deb_i2c (char*,...) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int dib3000_read_reg(struct dib3000_state *state, u16 reg)
{
	u8 wb[] = { ((reg >> 8) | 0x80) & 0xff, reg & 0xff };
	u8 rb[2];
	struct i2c_msg msg[] = {
		{ .addr = state->config.demod_address, .flags = 0,        .buf = wb, .len = 2 },
		{ .addr = state->config.demod_address, .flags = I2C_M_RD, .buf = rb, .len = 2 },
	};

	if (i2c_transfer(state->i2c, msg, 2) != 2)
		deb_i2c("i2c read error\n");

	deb_i2c("reading i2c bus (reg: %5d 0x%04x, val: %5d 0x%04x)\n",reg,reg,
			(rb[0] << 8) | rb[1],(rb[0] << 8) | rb[1]);

	return (rb[0] << 8) | rb[1];
}