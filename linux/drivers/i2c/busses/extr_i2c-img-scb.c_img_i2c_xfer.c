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
struct i2c_msg {int flags; int /*<<< orphan*/  len; } ;
struct img_i2c {scalar_t__ mode; int msg_status; int last_msg; int /*<<< orphan*/  check_timer; int /*<<< orphan*/  msg_complete; int /*<<< orphan*/  lock; struct i2c_msg msg; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct i2c_adapter {TYPE_1__ dev; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int I2C_M_IGNORE_NAK ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  IMG_I2C_TIMEOUT ; 
 scalar_t__ MODE_FATAL ; 
 scalar_t__ MODE_SUSPEND ; 
 int /*<<< orphan*/  SCB_CLEAR_REG ; 
 int /*<<< orphan*/  SCB_INT_CLEAR_REG ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct img_i2c* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  img_i2c_atomic_start (struct img_i2c*) ; 
 int /*<<< orphan*/  img_i2c_read (struct img_i2c*) ; 
 int /*<<< orphan*/  img_i2c_transaction_halt (struct img_i2c*,int) ; 
 int /*<<< orphan*/  img_i2c_write (struct img_i2c*) ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int img_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			int num)
{
	struct img_i2c *i2c = i2c_get_adapdata(adap);
	bool atomic = false;
	int i, ret;
	unsigned long time_left;

	if (i2c->mode == MODE_SUSPEND) {
		WARN(1, "refusing to service transaction in suspended state\n");
		return -EIO;
	}

	if (i2c->mode == MODE_FATAL)
		return -EIO;

	for (i = 0; i < num; i++) {
		/*
		 * 0 byte reads are not possible because the slave could try
		 * and pull the data line low, preventing a stop bit.
		 */
		if (!msgs[i].len && msgs[i].flags & I2C_M_RD)
			return -EIO;
		/*
		 * 0 byte writes are possible and used for probing, but we
		 * cannot do them in automatic mode, so use atomic mode
		 * instead.
		 *
		 * Also, the I2C_M_IGNORE_NAK mode can only be implemented
		 * in atomic mode.
		 */
		if (!msgs[i].len ||
		    (msgs[i].flags & I2C_M_IGNORE_NAK))
			atomic = true;
	}

	ret = pm_runtime_get_sync(adap->dev.parent);
	if (ret < 0)
		return ret;

	for (i = 0; i < num; i++) {
		struct i2c_msg *msg = &msgs[i];
		unsigned long flags;

		spin_lock_irqsave(&i2c->lock, flags);

		/*
		 * Make a copy of the message struct. We mustn't modify the
		 * original or we'll confuse drivers and i2c-dev.
		 */
		i2c->msg = *msg;
		i2c->msg_status = 0;

		/*
		 * After the last message we must have waited for a stop bit.
		 * Not waiting can cause problems when the clock is disabled
		 * before the stop bit is sent, and the linux I2C interface
		 * requires separate transfers not to joined with repeated
		 * start.
		 */
		i2c->last_msg = (i == num - 1);
		reinit_completion(&i2c->msg_complete);

		/*
		 * Clear line status and all interrupts before starting a
		 * transfer, as we may have unserviced interrupts from
		 * previous transfers that might be handled in the context
		 * of the new transfer.
		 */
		img_i2c_writel(i2c, SCB_INT_CLEAR_REG, ~0);
		img_i2c_writel(i2c, SCB_CLEAR_REG, ~0);

		if (atomic) {
			img_i2c_atomic_start(i2c);
		} else {
			/*
			 * Enable transaction halt if not the last message in
			 * the queue so that we can control repeated starts.
			 */
			img_i2c_transaction_halt(i2c, !i2c->last_msg);

			if (msg->flags & I2C_M_RD)
				img_i2c_read(i2c);
			else
				img_i2c_write(i2c);

			/*
			 * Release and then enable transaction halt, to
			 * allow only a single byte to proceed.
			 * This doesn't have an effect on the initial transfer
			 * but will allow the following transfers to start
			 * processing if the previous transfer was marked as
			 * complete while the i2c block was halted.
			 */
			img_i2c_transaction_halt(i2c, false);
			img_i2c_transaction_halt(i2c, !i2c->last_msg);
		}
		spin_unlock_irqrestore(&i2c->lock, flags);

		time_left = wait_for_completion_timeout(&i2c->msg_complete,
						      IMG_I2C_TIMEOUT);
		del_timer_sync(&i2c->check_timer);

		if (time_left == 0) {
			dev_err(adap->dev.parent, "i2c transfer timed out\n");
			i2c->msg_status = -ETIMEDOUT;
			break;
		}

		if (i2c->msg_status)
			break;
	}

	pm_runtime_mark_last_busy(adap->dev.parent);
	pm_runtime_put_autosuspend(adap->dev.parent);

	return i2c->msg_status ? i2c->msg_status : num;
}