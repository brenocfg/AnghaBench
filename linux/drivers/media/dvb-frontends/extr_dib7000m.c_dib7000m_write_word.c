#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct i2c_msg {int dummy; } ;
struct dib7000m_state {int* i2c_write_buffer; int i2c_addr; int /*<<< orphan*/  i2c_buffer_lock; TYPE_1__* msg; int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_3__ {int addr; int* buf; int len; scalar_t__ flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib7000m_write_word(struct dib7000m_state *state, u16 reg, u16 val)
{
	int ret;

	if (mutex_lock_interruptible(&state->i2c_buffer_lock) < 0) {
		dprintk("could not acquire lock\n");
		return -EINVAL;
	}

	state->i2c_write_buffer[0] = (reg >> 8) & 0xff;
	state->i2c_write_buffer[1] = reg & 0xff;
	state->i2c_write_buffer[2] = (val >> 8) & 0xff;
	state->i2c_write_buffer[3] = val & 0xff;

	memset(&state->msg[0], 0, sizeof(struct i2c_msg));
	state->msg[0].addr = state->i2c_addr >> 1;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_write_buffer;
	state->msg[0].len = 4;

	ret = (i2c_transfer(state->i2c_adap, state->msg, 1) != 1 ?
			-EREMOTEIO : 0);
	mutex_unlock(&state->i2c_buffer_lock);
	return ret;
}