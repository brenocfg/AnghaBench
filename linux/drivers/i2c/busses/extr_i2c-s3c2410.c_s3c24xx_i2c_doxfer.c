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
struct s3c24xx_i2c {int msg_num; int msg_idx; int quirks; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; int /*<<< orphan*/  wait; scalar_t__ msg_ptr; struct i2c_msg* msg; } ;
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int HZ ; 
 int QUIRK_HDMIPHY ; 
 int QUIRK_POLL ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  STATE_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  s3c24xx_i2c_disable_bus (struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_enable_irq (struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_message_start (struct s3c24xx_i2c*,struct i2c_msg*) ; 
 int s3c24xx_i2c_set_master (struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_wait_idle (struct s3c24xx_i2c*) ; 
 unsigned long wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int s3c24xx_i2c_doxfer(struct s3c24xx_i2c *i2c,
			      struct i2c_msg *msgs, int num)
{
	unsigned long timeout;
	int ret;

	ret = s3c24xx_i2c_set_master(i2c);
	if (ret != 0) {
		dev_err(i2c->dev, "cannot get bus (error %d)\n", ret);
		ret = -EAGAIN;
		goto out;
	}

	i2c->msg     = msgs;
	i2c->msg_num = num;
	i2c->msg_ptr = 0;
	i2c->msg_idx = 0;
	i2c->state   = STATE_START;

	s3c24xx_i2c_enable_irq(i2c);
	s3c24xx_i2c_message_start(i2c, msgs);

	if (i2c->quirks & QUIRK_POLL) {
		ret = i2c->msg_idx;

		if (ret != num)
			dev_dbg(i2c->dev, "incomplete xfer (%d)\n", ret);

		goto out;
	}

	timeout = wait_event_timeout(i2c->wait, i2c->msg_num == 0, HZ * 5);

	ret = i2c->msg_idx;

	/*
	 * Having these next two as dev_err() makes life very
	 * noisy when doing an i2cdetect
	 */
	if (timeout == 0)
		dev_dbg(i2c->dev, "timeout\n");
	else if (ret != num)
		dev_dbg(i2c->dev, "incomplete xfer (%d)\n", ret);

	/* For QUIRK_HDMIPHY, bus is already disabled */
	if (i2c->quirks & QUIRK_HDMIPHY)
		goto out;

	s3c24xx_i2c_wait_idle(i2c);

	s3c24xx_i2c_disable_bus(i2c);

 out:
	i2c->state = STATE_IDLE;

	return ret;
}