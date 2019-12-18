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
struct owl_i2c_dev {int msg_ptr; scalar_t__ err; scalar_t__ base; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_complete; struct i2c_msg* msg; } ;
struct i2c_msg {int len; unsigned int* buf; int flags; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int I2C_M_IGNORE_NAK ; 
 int I2C_M_RD ; 
 unsigned int OWL_I2C_CMD_AS (int) ; 
 unsigned int OWL_I2C_CMD_DE ; 
 unsigned int OWL_I2C_CMD_MSS ; 
 unsigned int OWL_I2C_CMD_NS ; 
 unsigned int OWL_I2C_CMD_RBE ; 
 unsigned int OWL_I2C_CMD_SAS (int) ; 
 unsigned int OWL_I2C_CMD_SBE ; 
 unsigned int OWL_I2C_CMD_SE ; 
 unsigned int OWL_I2C_CMD_SECL ; 
 int OWL_I2C_CTL_EN ; 
 int OWL_I2C_CTL_GBCC_STOP ; 
 int OWL_I2C_CTL_IRQE ; 
 int OWL_I2C_CTL_RB ; 
 int OWL_I2C_FIFOCTL_NIB ; 
 int OWL_I2C_FIFOSTAT_TFF ; 
 scalar_t__ OWL_I2C_REG_CMD ; 
 scalar_t__ OWL_I2C_REG_CTL ; 
 scalar_t__ OWL_I2C_REG_DATCNT ; 
 scalar_t__ OWL_I2C_REG_FIFOCTL ; 
 scalar_t__ OWL_I2C_REG_FIFOSTAT ; 
 scalar_t__ OWL_I2C_REG_STAT ; 
 scalar_t__ OWL_I2C_REG_TXDAT ; 
 unsigned int OWL_I2C_STAT_LAB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 struct owl_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int owl_i2c_check_bus_busy (struct i2c_adapter*) ; 
 int /*<<< orphan*/  owl_i2c_reset (struct owl_i2c_dev*) ; 
 int owl_i2c_reset_fifo (struct owl_i2c_dev*) ; 
 int /*<<< orphan*/  owl_i2c_set_freq (struct owl_i2c_dev*) ; 
 int /*<<< orphan*/  owl_i2c_update_reg (scalar_t__,int,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int owl_i2c_master_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			       int num)
{
	struct owl_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	struct i2c_msg *msg;
	unsigned long time_left, flags;
	unsigned int i2c_cmd, val;
	unsigned int addr;
	int ret, idx;

	spin_lock_irqsave(&i2c_dev->lock, flags);

	/* Reset I2C controller */
	owl_i2c_reset(i2c_dev);

	/* Set bus frequency */
	owl_i2c_set_freq(i2c_dev);

	/*
	 * Spinlock should be released before calling reset FIFO and
	 * bus busy check since those functions may sleep
	 */
	spin_unlock_irqrestore(&i2c_dev->lock, flags);

	/* Reset FIFO */
	ret = owl_i2c_reset_fifo(i2c_dev);
	if (ret)
		goto unlocked_err_exit;

	/* Check for bus busy */
	ret = owl_i2c_check_bus_busy(adap);
	if (ret)
		goto unlocked_err_exit;

	spin_lock_irqsave(&i2c_dev->lock, flags);

	/* Check for Arbitration lost */
	val = readl(i2c_dev->base + OWL_I2C_REG_STAT);
	if (val & OWL_I2C_STAT_LAB) {
		val &= ~OWL_I2C_STAT_LAB;
		writel(val, i2c_dev->base + OWL_I2C_REG_STAT);
		ret = -EAGAIN;
		goto err_exit;
	}

	reinit_completion(&i2c_dev->msg_complete);

	/* Enable I2C controller interrupt */
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
			   OWL_I2C_CTL_IRQE, true);

	/*
	 * Select: FIFO enable, Master mode, Stop enable, Data count enable,
	 * Send start bit
	 */
	i2c_cmd = OWL_I2C_CMD_SECL | OWL_I2C_CMD_MSS | OWL_I2C_CMD_SE |
		  OWL_I2C_CMD_NS | OWL_I2C_CMD_DE | OWL_I2C_CMD_SBE;

	/* Handle repeated start condition */
	if (num > 1) {
		/* Set internal address length and enable repeated start */
		i2c_cmd |= OWL_I2C_CMD_AS(msgs[0].len + 1) |
			   OWL_I2C_CMD_SAS(1) | OWL_I2C_CMD_RBE;

		/* Write slave address */
		addr = i2c_8bit_addr_from_msg(&msgs[0]);
		writel(addr, i2c_dev->base + OWL_I2C_REG_TXDAT);

		/* Write internal register address */
		for (idx = 0; idx < msgs[0].len; idx++)
			writel(msgs[0].buf[idx],
			       i2c_dev->base + OWL_I2C_REG_TXDAT);

		msg = &msgs[1];
	} else {
		/* Set address length */
		i2c_cmd |= OWL_I2C_CMD_AS(1);
		msg = &msgs[0];
	}

	i2c_dev->msg = msg;
	i2c_dev->msg_ptr = 0;

	/* Set data count for the message */
	writel(msg->len, i2c_dev->base + OWL_I2C_REG_DATCNT);

	addr = i2c_8bit_addr_from_msg(msg);
	writel(addr, i2c_dev->base + OWL_I2C_REG_TXDAT);

	if (!(msg->flags & I2C_M_RD)) {
		/* Write data to FIFO */
		for (idx = 0; idx < msg->len; idx++) {
			/* Check for FIFO full */
			if (readl(i2c_dev->base + OWL_I2C_REG_FIFOSTAT) &
			    OWL_I2C_FIFOSTAT_TFF)
				break;

			writel(msg->buf[idx],
			       i2c_dev->base + OWL_I2C_REG_TXDAT);
		}

		i2c_dev->msg_ptr = idx;
	}

	/* Ignore the NACK if needed */
	if (msg->flags & I2C_M_IGNORE_NAK)
		owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_FIFOCTL,
				   OWL_I2C_FIFOCTL_NIB, true);
	else
		owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_FIFOCTL,
				   OWL_I2C_FIFOCTL_NIB, false);

	/* Start the transfer */
	writel(i2c_cmd, i2c_dev->base + OWL_I2C_REG_CMD);

	spin_unlock_irqrestore(&i2c_dev->lock, flags);

	time_left = wait_for_completion_timeout(&i2c_dev->msg_complete,
						adap->timeout);

	spin_lock_irqsave(&i2c_dev->lock, flags);
	if (time_left == 0) {
		dev_err(&adap->dev, "Transaction timed out\n");
		/* Send stop condition and release the bus */
		owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
				   OWL_I2C_CTL_GBCC_STOP | OWL_I2C_CTL_RB,
				   true);
		ret = -ETIMEDOUT;
		goto err_exit;
	}

	ret = i2c_dev->err < 0 ? i2c_dev->err : num;

err_exit:
	spin_unlock_irqrestore(&i2c_dev->lock, flags);

unlocked_err_exit:
	/* Disable I2C controller */
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
			   OWL_I2C_CTL_EN, false);

	return ret;
}