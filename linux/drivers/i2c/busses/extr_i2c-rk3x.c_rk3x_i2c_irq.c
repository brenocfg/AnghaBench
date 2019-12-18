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
struct rk3x_i2c {int state; int /*<<< orphan*/  lock; TYPE_1__* msg; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int I2C_M_IGNORE_NAK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int REG_INT_ALL ; 
 unsigned int REG_INT_BRF ; 
 unsigned int REG_INT_BTF ; 
 unsigned int REG_INT_NAKRCV ; 
 int /*<<< orphan*/  REG_IPD ; 
#define  STATE_IDLE 132 
#define  STATE_READ 131 
#define  STATE_START 130 
#define  STATE_STOP 129 
#define  STATE_WRITE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int i2c_readl (struct rk3x_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_writel (struct rk3x_i2c*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3x_i2c_clean_ipd (struct rk3x_i2c*) ; 
 int /*<<< orphan*/  rk3x_i2c_handle_read (struct rk3x_i2c*,unsigned int) ; 
 int /*<<< orphan*/  rk3x_i2c_handle_start (struct rk3x_i2c*,unsigned int) ; 
 int /*<<< orphan*/  rk3x_i2c_handle_stop (struct rk3x_i2c*,unsigned int) ; 
 int /*<<< orphan*/  rk3x_i2c_handle_write (struct rk3x_i2c*,unsigned int) ; 
 int /*<<< orphan*/  rk3x_i2c_stop (struct rk3x_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rk3x_i2c_irq(int irqno, void *dev_id)
{
	struct rk3x_i2c *i2c = dev_id;
	unsigned int ipd;

	spin_lock(&i2c->lock);

	ipd = i2c_readl(i2c, REG_IPD);
	if (i2c->state == STATE_IDLE) {
		dev_warn(i2c->dev, "irq in STATE_IDLE, ipd = 0x%x\n", ipd);
		rk3x_i2c_clean_ipd(i2c);
		goto out;
	}

	dev_dbg(i2c->dev, "IRQ: state %d, ipd: %x\n", i2c->state, ipd);

	/* Clean interrupt bits we don't care about */
	ipd &= ~(REG_INT_BRF | REG_INT_BTF);

	if (ipd & REG_INT_NAKRCV) {
		/*
		 * We got a NACK in the last operation. Depending on whether
		 * IGNORE_NAK is set, we have to stop the operation and report
		 * an error.
		 */
		i2c_writel(i2c, REG_INT_NAKRCV, REG_IPD);

		ipd &= ~REG_INT_NAKRCV;

		if (!(i2c->msg->flags & I2C_M_IGNORE_NAK))
			rk3x_i2c_stop(i2c, -ENXIO);
	}

	/* is there anything left to handle? */
	if ((ipd & REG_INT_ALL) == 0)
		goto out;

	switch (i2c->state) {
	case STATE_START:
		rk3x_i2c_handle_start(i2c, ipd);
		break;
	case STATE_WRITE:
		rk3x_i2c_handle_write(i2c, ipd);
		break;
	case STATE_READ:
		rk3x_i2c_handle_read(i2c, ipd);
		break;
	case STATE_STOP:
		rk3x_i2c_handle_stop(i2c, ipd);
		break;
	case STATE_IDLE:
		break;
	}

out:
	spin_unlock(&i2c->lock);
	return IRQ_HANDLED;
}