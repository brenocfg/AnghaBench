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
struct cx24120_state {TYPE_2__* i2c; TYPE_1__* config; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_transfer (TYPE_2__*,struct i2c_msg*,int) ; 

__attribute__((used)) static int cx24120_writereg(struct cx24120_state *state, u8 reg, u8 data)
{
	u8 buf[] = { reg, data };
	struct i2c_msg msg = {
		.addr = state->config->i2c_addr,
		.flags = 0,
		.buf = buf,
		.len = 2
	};
	int ret;

	ret = i2c_transfer(state->i2c, &msg, 1);
	if (ret != 1) {
		err("Write error: i2c_write error(err == %i, 0x%02x: 0x%02x)\n",
		    ret, reg, data);
		return ret;
	}

	dev_dbg(&state->i2c->dev, "reg=0x%02x; data=0x%02x\n", reg, data);

	return 0;
}