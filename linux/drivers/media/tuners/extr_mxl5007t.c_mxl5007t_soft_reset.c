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
struct TYPE_2__ {int /*<<< orphan*/  adap; int /*<<< orphan*/  addr; } ;
struct mxl5007t_state {TYPE_1__ i2c_props; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  mxl_err (char*) ; 

__attribute__((used)) static int mxl5007t_soft_reset(struct mxl5007t_state *state)
{
	u8 d = 0xff;
	struct i2c_msg msg = {
		.addr = state->i2c_props.addr, .flags = 0,
		.buf = &d, .len = 1
	};
	int ret = i2c_transfer(state->i2c_props.adap, &msg, 1);

	if (ret != 1) {
		mxl_err("failed!");
		return -EREMOTEIO;
	}
	return 0;
}