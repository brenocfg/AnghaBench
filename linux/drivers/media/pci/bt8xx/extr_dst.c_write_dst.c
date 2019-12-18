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
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dst_state {int /*<<< orphan*/  i2c; TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  dst_error_bailout (struct dst_state*) ; 
 int /*<<< orphan*/  dst_error_recovery (struct dst_state*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

int write_dst(struct dst_state *state, u8 *data, u8 len)
{
	struct i2c_msg msg = {
		.addr = state->config->demod_address,
		.flags = 0,
		.buf = data,
		.len = len
	};

	int err;
	u8 cnt;

	dprintk(1, "writing [ %*ph ]\n", len, data);

	for (cnt = 0; cnt < 2; cnt++) {
		if ((err = i2c_transfer(state->i2c, &msg, 1)) < 0) {
			dprintk(2, "_write_dst error (err == %i, len == 0x%02x, b0 == 0x%02x)\n",
				err, len, data[0]);
			dst_error_recovery(state);
			continue;
		} else
			break;
	}
	if (cnt >= 2) {
		dprintk(2, "RDC 8820 RESET\n");
		dst_error_bailout(state);

		return -1;
	}

	return 0;
}