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
struct synquacer_i2c {int msg_num; int msg_idx; int /*<<< orphan*/  speed_khz; int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  completion; struct i2c_msg* msg; int /*<<< orphan*/  state; scalar_t__ msg_ptr; scalar_t__ base; } ;
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  STATE_START ; 
 unsigned char SYNQUACER_I2C_BSR_BB ; 
 scalar_t__ SYNQUACER_I2C_REG_BSR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synquacer_i2c_hw_init (struct synquacer_i2c*) ; 
 int synquacer_i2c_master_start (struct synquacer_i2c*,struct i2c_msg*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synquacer_i2c_doxfer(struct synquacer_i2c *i2c,
				struct i2c_msg *msgs, int num)
{
	unsigned char bsr;
	unsigned long timeout;
	int ret;

	synquacer_i2c_hw_init(i2c);
	bsr = readb(i2c->base + SYNQUACER_I2C_REG_BSR);
	if (bsr & SYNQUACER_I2C_BSR_BB) {
		dev_err(i2c->dev, "cannot get bus (bus busy)\n");
		return -EBUSY;
	}

	reinit_completion(&i2c->completion);

	i2c->msg = msgs;
	i2c->msg_num = num;
	i2c->msg_ptr = 0;
	i2c->msg_idx = 0;
	i2c->state = STATE_START;

	ret = synquacer_i2c_master_start(i2c, i2c->msg);
	if (ret < 0) {
		dev_dbg(i2c->dev, "Address failed: (%d)\n", ret);
		return ret;
	}

	timeout = wait_for_completion_timeout(&i2c->completion,
					msecs_to_jiffies(i2c->timeout_ms));
	if (timeout == 0) {
		dev_dbg(i2c->dev, "timeout\n");
		return -EAGAIN;
	}

	ret = i2c->msg_idx;
	if (ret != num) {
		dev_dbg(i2c->dev, "incomplete xfer (%d)\n", ret);
		return -EAGAIN;
	}

	/* wait 2 clock periods to ensure the stop has been through the bus */
	udelay(DIV_ROUND_UP(2 * 1000, i2c->speed_khz));

	return ret;
}