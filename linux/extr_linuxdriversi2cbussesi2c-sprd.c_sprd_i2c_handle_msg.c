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
struct sprd_i2c {int err; int /*<<< orphan*/  complete; int /*<<< orphan*/  count; int /*<<< orphan*/  buf; struct i2c_msg* msg; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct i2c_adapter {struct sprd_i2c* algo_data; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprd_i2c_data_transfer (struct sprd_i2c*) ; 
 int /*<<< orphan*/  sprd_i2c_opt_mode (struct sprd_i2c*,int) ; 
 int /*<<< orphan*/  sprd_i2c_opt_start (struct sprd_i2c*) ; 
 int /*<<< orphan*/  sprd_i2c_reset_fifo (struct sprd_i2c*) ; 
 int /*<<< orphan*/  sprd_i2c_send_stop (struct sprd_i2c*,int) ; 
 int /*<<< orphan*/  sprd_i2c_set_count (struct sprd_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_i2c_set_devaddr (struct sprd_i2c*,struct i2c_msg*) ; 
 int /*<<< orphan*/  sprd_i2c_set_fifo_full_int (struct sprd_i2c*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sprd_i2c_handle_msg(struct i2c_adapter *i2c_adap,
			       struct i2c_msg *msg, bool is_last_msg)
{
	struct sprd_i2c *i2c_dev = i2c_adap->algo_data;

	i2c_dev->msg = msg;
	i2c_dev->buf = msg->buf;
	i2c_dev->count = msg->len;

	reinit_completion(&i2c_dev->complete);
	sprd_i2c_reset_fifo(i2c_dev);
	sprd_i2c_set_devaddr(i2c_dev, msg);
	sprd_i2c_set_count(i2c_dev, msg->len);

	if (msg->flags & I2C_M_RD) {
		sprd_i2c_opt_mode(i2c_dev, 1);
		sprd_i2c_send_stop(i2c_dev, 1);
	} else {
		sprd_i2c_opt_mode(i2c_dev, 0);
		sprd_i2c_send_stop(i2c_dev, !!is_last_msg);
	}

	/*
	 * We should enable rx fifo full interrupt to get data when receiving
	 * full data.
	 */
	if (msg->flags & I2C_M_RD)
		sprd_i2c_set_fifo_full_int(i2c_dev, 1);
	else
		sprd_i2c_data_transfer(i2c_dev);

	sprd_i2c_opt_start(i2c_dev);

	wait_for_completion(&i2c_dev->complete);

	return i2c_dev->err;
}