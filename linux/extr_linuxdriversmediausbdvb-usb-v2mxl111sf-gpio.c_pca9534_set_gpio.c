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
struct mxl111sf_state {TYPE_1__* d; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  PCA9534_I2C_ADDR ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  mxl_debug (char*,int,int) ; 

__attribute__((used)) static int pca9534_set_gpio(struct mxl111sf_state *state, int gpio, int val)
{
	u8 w[2] = { 1, 0 };
	u8 r = 0;
	struct i2c_msg msg[] = {
		{ .addr = PCA9534_I2C_ADDR,
		  .flags = 0, .buf = w, .len = 1 },
		{ .addr = PCA9534_I2C_ADDR,
		  .flags = I2C_M_RD, .buf = &r, .len = 1 },
	};

	mxl_debug("(%d, %d)", gpio, val);

	/* read current GPIO levels from flip-flop */
	i2c_transfer(&state->d->i2c_adap, msg, 2);

	/* prepare write buffer with current GPIO levels */
	msg[0].len = 2;
#if 0
	w[0] = 1;
#endif
	w[1] = r;

	/* clear the desired GPIO */
	w[1] &= ~(1 << gpio);

	/* set the desired GPIO value */
	w[1] |= ((val ? 1 : 0) << gpio);

	/* write new GPIO levels to flip-flop */
	i2c_transfer(&state->d->i2c_adap, &msg[0], 1);

	return 0;
}