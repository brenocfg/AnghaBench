#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct i2c_msg {int dummy; } ;
struct dib0070_state {int* i2c_write_buffer; int /*<<< orphan*/  i2c_buffer_lock; TYPE_2__* msg; int /*<<< orphan*/  i2c; TYPE_1__* cfg; } ;
struct TYPE_5__ {int* buf; int len; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_address; } ;

/* Variables and functions */
 int EINVAL ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int dib0070_write_reg(struct dib0070_state *state, u8 reg, u16 val)
{
	int ret;

	if (mutex_lock_interruptible(&state->i2c_buffer_lock) < 0) {
		dprintk("could not acquire lock\n");
		return -EINVAL;
	}
	state->i2c_write_buffer[0] = reg;
	state->i2c_write_buffer[1] = val >> 8;
	state->i2c_write_buffer[2] = val & 0xff;

	memset(state->msg, 0, sizeof(struct i2c_msg));
	state->msg[0].addr = state->cfg->i2c_address;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_write_buffer;
	state->msg[0].len = 3;

	if (i2c_transfer(state->i2c, state->msg, 1) != 1) {
		pr_warn("DiB0070 I2C write failed\n");
		ret = -EREMOTEIO;
	} else
		ret = 0;

	mutex_unlock(&state->i2c_buffer_lock);
	return ret;
}