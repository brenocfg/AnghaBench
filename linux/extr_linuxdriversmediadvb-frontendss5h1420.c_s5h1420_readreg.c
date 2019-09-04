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
struct s5h1420_state {int* shadow; int /*<<< orphan*/  i2c; TYPE_1__* config; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {scalar_t__ repeated_start_workaround; int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static u8 s5h1420_readreg(struct s5h1420_state *state, u8 reg)
{
	int ret;
	u8 b[2];
	struct i2c_msg msg[] = {
		{ .addr = state->config->demod_address, .flags = 0, .buf = b, .len = 2 },
		{ .addr = state->config->demod_address, .flags = 0, .buf = &reg, .len = 1 },
		{ .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b, .len = 1 },
	};

	b[0] = (reg - 1) & 0xff;
	b[1] = state->shadow[(reg - 1) & 0xff];

	if (state->config->repeated_start_workaround) {
		ret = i2c_transfer(state->i2c, msg, 3);
		if (ret != 3)
			return ret;
	} else {
		ret = i2c_transfer(state->i2c, &msg[1], 1);
		if (ret != 1)
			return ret;
		ret = i2c_transfer(state->i2c, &msg[2], 1);
		if (ret != 1)
			return ret;
	}

	/* dprintk("rd(%02x): %02x %02x\n", state->config->demod_address, reg, b[0]); */

	return b[0];
}