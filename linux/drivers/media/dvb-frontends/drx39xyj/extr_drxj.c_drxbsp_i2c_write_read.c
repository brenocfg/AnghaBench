#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u16 ;
struct i2c_msg {int addr; void* len; int /*<<< orphan*/ * buf; void* flags; } ;
struct i2c_device_addr {int i2c_addr; struct drx39xxj_state* user_data; } ;
struct drx39xxj_state {int /*<<< orphan*/ * i2c; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 void* I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int drxbsp_i2c_write_read(struct i2c_device_addr *w_dev_addr,
				 u16 w_count,
				 u8 *wData,
				 struct i2c_device_addr *r_dev_addr,
				 u16 r_count, u8 *r_data)
{
	struct drx39xxj_state *state;
	struct i2c_msg msg[2];
	unsigned int num_msgs;

	if (w_dev_addr == NULL) {
		/* Read only */
		state = r_dev_addr->user_data;
		msg[0].addr = r_dev_addr->i2c_addr >> 1;
		msg[0].flags = I2C_M_RD;
		msg[0].buf = r_data;
		msg[0].len = r_count;
		num_msgs = 1;
	} else if (r_dev_addr == NULL) {
		/* Write only */
		state = w_dev_addr->user_data;
		msg[0].addr = w_dev_addr->i2c_addr >> 1;
		msg[0].flags = 0;
		msg[0].buf = wData;
		msg[0].len = w_count;
		num_msgs = 1;
	} else {
		/* Both write and read */
		state = w_dev_addr->user_data;
		msg[0].addr = w_dev_addr->i2c_addr >> 1;
		msg[0].flags = 0;
		msg[0].buf = wData;
		msg[0].len = w_count;
		msg[1].addr = r_dev_addr->i2c_addr >> 1;
		msg[1].flags = I2C_M_RD;
		msg[1].buf = r_data;
		msg[1].len = r_count;
		num_msgs = 2;
	}

	if (state->i2c == NULL) {
		pr_err("i2c was zero, aborting\n");
		return 0;
	}
	if (i2c_transfer(state->i2c, msg, num_msgs) != num_msgs) {
		pr_warn("drx3933: I2C write/read failed\n");
		return -EREMOTEIO;
	}

#ifdef DJH_DEBUG
	if (w_dev_addr == NULL || r_dev_addr == NULL)
		return 0;

	state = w_dev_addr->user_data;

	if (state->i2c == NULL)
		return 0;

	msg[0].addr = w_dev_addr->i2c_addr;
	msg[0].flags = 0;
	msg[0].buf = wData;
	msg[0].len = w_count;
	msg[1].addr = r_dev_addr->i2c_addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = r_data;
	msg[1].len = r_count;
	num_msgs = 2;

	pr_debug("drx3933 i2c operation addr=%x i2c=%p, wc=%x rc=%x\n",
	       w_dev_addr->i2c_addr, state->i2c, w_count, r_count);

	if (i2c_transfer(state->i2c, msg, 2) != 2) {
		pr_warn("drx3933: I2C write/read failed\n");
		return -EREMOTEIO;
	}
#endif
	return 0;
}