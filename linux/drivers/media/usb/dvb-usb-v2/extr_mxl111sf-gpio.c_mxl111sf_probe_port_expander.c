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
struct mxl111sf_state {int port_expander_addr; void* gpio_port_expander; TYPE_1__* d; } ;
struct i2c_msg {int* buf; int len; int addr; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 void* mxl111sf_PCA9534 ; 
 void* mxl111sf_gpio_hw ; 
 int /*<<< orphan*/  mxl_debug (char*,...) ; 

__attribute__((used)) static int mxl111sf_probe_port_expander(struct mxl111sf_state *state)
{
	int ret;
	u8 w = 1;
	u8 r = 0;
	struct i2c_msg msg[] = {
		{ .flags = 0,        .buf = &w, .len = 1 },
		{ .flags = I2C_M_RD, .buf = &r, .len = 1 },
	};

	mxl_debug("()");

	msg[0].addr = 0x70 >> 1;
	msg[1].addr = 0x70 >> 1;

	/* read current GPIO levels from flip-flop */
	ret = i2c_transfer(&state->d->i2c_adap, msg, 2);
	if (ret == 2) {
		state->port_expander_addr = msg[0].addr;
		state->gpio_port_expander = mxl111sf_PCA9534;
		mxl_debug("found port expander at 0x%02x",
			  state->port_expander_addr);
		return 0;
	}

	msg[0].addr = 0x40 >> 1;
	msg[1].addr = 0x40 >> 1;

	ret = i2c_transfer(&state->d->i2c_adap, msg, 2);
	if (ret == 2) {
		state->port_expander_addr = msg[0].addr;
		state->gpio_port_expander = mxl111sf_PCA9534;
		mxl_debug("found port expander at 0x%02x",
			  state->port_expander_addr);
		return 0;
	}
	state->port_expander_addr = 0xff;
	state->gpio_port_expander = mxl111sf_gpio_hw;
	mxl_debug("using hardware gpio");
	return 0;
}