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
struct i2c_msg {int dummy; } ;
struct dc_i2c {int last; int error; int /*<<< orphan*/  state; int /*<<< orphan*/  done; int /*<<< orphan*/  lock; scalar_t__ msgbuf_ptr; struct i2c_msg* msg; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  TIMEOUT_MS ; 
 int /*<<< orphan*/  dc_i2c_set_irq (struct dc_i2c*,int) ; 
 int /*<<< orphan*/  dc_i2c_start_msg (struct dc_i2c*,int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dc_i2c_xfer_msg(struct dc_i2c *i2c, struct i2c_msg *msg, int first,
			   int last)
{
	unsigned long timeout = msecs_to_jiffies(TIMEOUT_MS);
	unsigned long flags;

	spin_lock_irqsave(&i2c->lock, flags);
	i2c->msg = msg;
	i2c->msgbuf_ptr = 0;
	i2c->last = last;
	i2c->error = 0;

	reinit_completion(&i2c->done);
	dc_i2c_set_irq(i2c, 1);
	dc_i2c_start_msg(i2c, first);
	spin_unlock_irqrestore(&i2c->lock, flags);

	timeout = wait_for_completion_timeout(&i2c->done, timeout);
	dc_i2c_set_irq(i2c, 0);
	if (timeout == 0) {
		i2c->state = STATE_IDLE;
		return -ETIMEDOUT;
	}

	if (i2c->error)
		return i2c->error;

	return 0;
}