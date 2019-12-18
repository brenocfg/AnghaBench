#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;
struct img_i2c {int line_status; scalar_t__ mode; int int_enable; int /*<<< orphan*/  lock; int /*<<< orphan*/  last_msg; TYPE_3__ msg; TYPE_2__ adap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int I2C_M_RD ; 
 int INT_FIFO_EMPTY ; 
 int INT_FIFO_FULL ; 
 int INT_LEVEL ; 
 int INT_SCLK_LOW_TIMEOUT ; 
 int INT_SLAVE_EVENT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int ISR_COMPLETE (int /*<<< orphan*/ ) ; 
 unsigned int ISR_COMPLETE_M ; 
 unsigned int ISR_FATAL (int /*<<< orphan*/ ) ; 
 unsigned int ISR_FATAL_M ; 
 unsigned int ISR_STATUS_M ; 
 unsigned int ISR_WAITSTOP ; 
 int LINESTAT_CLEAR_SHIFT ; 
 int LINESTAT_INPUT_DATA ; 
 int LINESTAT_LATCHED ; 
 int LINESTAT_STOP_BIT_DET ; 
 scalar_t__ MODE_ATOMIC ; 
 scalar_t__ MODE_AUTOMATIC ; 
 scalar_t__ MODE_FATAL ; 
 scalar_t__ MODE_RAW ; 
 scalar_t__ MODE_SEQUENCE ; 
 scalar_t__ MODE_WAITSTOP ; 
 int /*<<< orphan*/  SCB_CLEAR_REG ; 
 int /*<<< orphan*/  SCB_INT_CLEAR_REG ; 
 int /*<<< orphan*/  SCB_INT_MASK_REG ; 
 int /*<<< orphan*/  SCB_INT_STATUS_REG ; 
 int /*<<< orphan*/  SCB_STATUS_REG ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 unsigned int img_i2c_atomic (struct img_i2c*,int,int) ; 
 unsigned int img_i2c_auto (struct img_i2c*,int,int) ; 
 int /*<<< orphan*/  img_i2c_complete_transaction (struct img_i2c*,int) ; 
 unsigned int img_i2c_raw (struct img_i2c*,int,int) ; 
 int img_i2c_readl (struct img_i2c*,int /*<<< orphan*/ ) ; 
 unsigned int img_i2c_sequence (struct img_i2c*,int) ; 
 int /*<<< orphan*/  img_i2c_switch_mode (struct img_i2c*,scalar_t__) ; 
 int /*<<< orphan*/  img_i2c_wr_rd_fence (struct img_i2c*) ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t img_i2c_isr(int irq, void *dev_id)
{
	struct img_i2c *i2c = (struct img_i2c *)dev_id;
	u32 int_status, line_status;
	/* We handle transaction completion AFTER accessing registers */
	unsigned int hret;

	/* Read interrupt status register. */
	int_status = img_i2c_readl(i2c, SCB_INT_STATUS_REG);
	/* Clear detected interrupts. */
	img_i2c_writel(i2c, SCB_INT_CLEAR_REG, int_status);

	/*
	 * Read line status and clear it until it actually is clear.  We have
	 * to be careful not to lose any line status bits that get latched.
	 */
	line_status = img_i2c_readl(i2c, SCB_STATUS_REG);
	if (line_status & LINESTAT_LATCHED) {
		img_i2c_writel(i2c, SCB_CLEAR_REG,
			      (line_status & LINESTAT_LATCHED)
				>> LINESTAT_CLEAR_SHIFT);
		img_i2c_wr_rd_fence(i2c);
	}

	spin_lock(&i2c->lock);

	/* Keep track of line status bits received */
	i2c->line_status &= ~LINESTAT_INPUT_DATA;
	i2c->line_status |= line_status;

	/*
	 * Certain interrupts indicate that sclk low timeout is not
	 * a problem. If any of these are set, just continue.
	 */
	if ((int_status & INT_SCLK_LOW_TIMEOUT) &&
	    !(int_status & (INT_SLAVE_EVENT |
			    INT_FIFO_EMPTY |
			    INT_FIFO_FULL))) {
		dev_crit(i2c->adap.dev.parent,
			 "fatal: clock low timeout occurred %s addr 0x%02x\n",
			 (i2c->msg.flags & I2C_M_RD) ? "reading" : "writing",
			 i2c->msg.addr);
		hret = ISR_FATAL(EIO);
		goto out;
	}

	if (i2c->mode == MODE_ATOMIC)
		hret = img_i2c_atomic(i2c, int_status, line_status);
	else if (i2c->mode == MODE_AUTOMATIC)
		hret = img_i2c_auto(i2c, int_status, line_status);
	else if (i2c->mode == MODE_SEQUENCE)
		hret = img_i2c_sequence(i2c, int_status);
	else if (i2c->mode == MODE_WAITSTOP && (int_status & INT_SLAVE_EVENT) &&
			 (line_status & LINESTAT_STOP_BIT_DET))
		hret = ISR_COMPLETE(0);
	else if (i2c->mode == MODE_RAW)
		hret = img_i2c_raw(i2c, int_status, line_status);
	else
		hret = 0;

	/* Clear detected level interrupts. */
	img_i2c_writel(i2c, SCB_INT_CLEAR_REG, int_status & INT_LEVEL);

out:
	if (hret & ISR_WAITSTOP) {
		/*
		 * Only wait for stop on last message.
		 * Also we may already have detected the stop bit.
		 */
		if (!i2c->last_msg || i2c->line_status & LINESTAT_STOP_BIT_DET)
			hret = ISR_COMPLETE(0);
		else
			img_i2c_switch_mode(i2c, MODE_WAITSTOP);
	}

	/* now we've finished using regs, handle transaction completion */
	if (hret & ISR_COMPLETE_M) {
		int status = -(hret & ISR_STATUS_M);

		img_i2c_complete_transaction(i2c, status);
		if (hret & ISR_FATAL_M)
			img_i2c_switch_mode(i2c, MODE_FATAL);
	}

	/* Enable interrupts (int_enable may be altered by changing mode) */
	img_i2c_writel(i2c, SCB_INT_MASK_REG, i2c->int_enable);

	spin_unlock(&i2c->lock);

	return IRQ_HANDLED;
}