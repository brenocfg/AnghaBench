#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct cx24117_state {int /*<<< orphan*/  demod; TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* i2c; int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int i2c_transfer (TYPE_2__*,struct i2c_msg*,int) ; 

__attribute__((used)) static int cx24117_readregN(struct cx24117_state *state,
	u8 reg, u8 *buf, int len)
{
	int ret;
	struct i2c_msg msg[] = {
		{ .addr = state->priv->demod_address, .flags = 0,
			.buf = &reg, .len = 1 },
		{ .addr = state->priv->demod_address, .flags = I2C_M_RD,
			.buf = buf, .len = len }
	};

	ret = i2c_transfer(state->priv->i2c, msg, 2);
	if (ret < 0) {
		dev_warn(&state->priv->i2c->dev,
			"%s: demod%d i2c rd err(%d) @0x%x\n",
			KBUILD_MODNAME, state->demod, ret, reg);
		return ret;
	}
	return 0;
}