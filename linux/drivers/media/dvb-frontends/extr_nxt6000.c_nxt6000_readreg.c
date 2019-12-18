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
struct nxt6000_state {int /*<<< orphan*/  i2c; TYPE_1__* config; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static u8 nxt6000_readreg(struct nxt6000_state* state, u8 reg)
{
	int ret;
	u8 b0[] = { reg };
	u8 b1[] = { 0 };
	struct i2c_msg msgs[] = {
		{.addr = state->config->demod_address,.flags = 0,.buf = b0,.len = 1},
		{.addr = state->config->demod_address,.flags = I2C_M_RD,.buf = b1,.len = 1}
	};

	ret = i2c_transfer(state->i2c, msgs, 2);

	if (ret != 2)
		dprintk("nxt6000: nxt6000_read error (reg: 0x%02X, ret: %d)\n", reg, ret);

	return b1[0];
}