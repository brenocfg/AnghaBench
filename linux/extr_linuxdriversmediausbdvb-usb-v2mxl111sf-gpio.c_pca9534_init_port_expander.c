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
 int /*<<< orphan*/  PCA9534_I2C_ADDR ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  mxl_debug (char*) ; 

__attribute__((used)) static int pca9534_init_port_expander(struct mxl111sf_state *state)
{
	u8 w[2] = { 1, 0x07 }; /* write protect enabled, signal LEDs off */

	struct i2c_msg msg = {
		.addr = PCA9534_I2C_ADDR,
		.flags = 0, .buf = w, .len = 2
	};

	mxl_debug("()");

	i2c_transfer(&state->d->i2c_adap, &msg, 1);

	/* configure all pins as outputs */
	w[0] = 3;
	w[1] = 0;

	i2c_transfer(&state->d->i2c_adap, &msg, 1);

	return 0;
}