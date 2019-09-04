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
struct TYPE_3__ {int /*<<< orphan*/  demod_address; } ;
struct ec100_state {TYPE_2__* i2c; TYPE_1__ config; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int i2c_transfer (TYPE_2__*,struct i2c_msg*,int) ; 

__attribute__((used)) static int ec100_read_reg(struct ec100_state *state, u8 reg, u8 *val)
{
	int ret;
	struct i2c_msg msg[2] = {
		{
			.addr = state->config.demod_address,
			.flags = 0,
			.len = 1,
			.buf = &reg
		}, {
			.addr = state->config.demod_address,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = val
		}
	};

	ret = i2c_transfer(state->i2c, msg, 2);
	if (ret == 2) {
		ret = 0;
	} else {
		dev_warn(&state->i2c->dev, "%s: i2c rd failed=%d reg=%02x\n",
				KBUILD_MODNAME, ret, reg);
		ret = -EREMOTEIO;
	}

	return ret;
}