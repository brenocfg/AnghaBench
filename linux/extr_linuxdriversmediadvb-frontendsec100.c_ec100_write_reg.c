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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int i2c_transfer (TYPE_2__*,struct i2c_msg*,int) ; 

__attribute__((used)) static int ec100_write_reg(struct ec100_state *state, u8 reg, u8 val)
{
	int ret;
	u8 buf[2] = {reg, val};
	struct i2c_msg msg[1] = {
		{
			.addr = state->config.demod_address,
			.flags = 0,
			.len = sizeof(buf),
			.buf = buf,
		}
	};

	ret = i2c_transfer(state->i2c, msg, 1);
	if (ret == 1) {
		ret = 0;
	} else {
		dev_warn(&state->i2c->dev, "%s: i2c wr failed=%d reg=%02x\n",
				KBUILD_MODNAME, ret, reg);
		ret = -EREMOTEIO;
	}

	return ret;
}