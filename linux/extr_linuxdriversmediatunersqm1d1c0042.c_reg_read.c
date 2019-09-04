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
struct qm1d1c0042_state {TYPE_1__* i2c; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int reg_read(struct qm1d1c0042_state *state, u8 reg, u8 *val)
{
	struct i2c_msg msgs[2] = {
		{
			.addr = state->i2c->addr,
			.flags = 0,
			.buf = &reg,
			.len = 1,
		},
		{
			.addr = state->i2c->addr,
			.flags = I2C_M_RD,
			.buf = val,
			.len = 1,
		},
	};
	int ret;

	ret = i2c_transfer(state->i2c->adapter, msgs, ARRAY_SIZE(msgs));
	if (ret >= 0 && ret < ARRAY_SIZE(msgs))
		ret = -EIO;
	return (ret == ARRAY_SIZE(msgs)) ? 0 : ret;
}