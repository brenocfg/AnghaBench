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
struct rk3x_i2c {int busy; int /*<<< orphan*/  wait; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  REG_CON ; 
 unsigned int REG_CON_STOP ; 
 unsigned int REG_INT_STOP ; 
 int /*<<< orphan*/  REG_IPD ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int i2c_readl (struct rk3x_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_writel (struct rk3x_i2c*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3x_i2c_clean_ipd (struct rk3x_i2c*) ; 
 int /*<<< orphan*/  rk3x_i2c_stop (struct rk3x_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rk3x_i2c_handle_stop(struct rk3x_i2c *i2c, unsigned int ipd)
{
	unsigned int con;

	if (!(ipd & REG_INT_STOP)) {
		rk3x_i2c_stop(i2c, -EIO);
		dev_err(i2c->dev, "unexpected irq in STOP: 0x%x\n", ipd);
		rk3x_i2c_clean_ipd(i2c);
		return;
	}

	/* ack interrupt */
	i2c_writel(i2c, REG_INT_STOP, REG_IPD);

	/* disable STOP bit */
	con = i2c_readl(i2c, REG_CON);
	con &= ~REG_CON_STOP;
	i2c_writel(i2c, con, REG_CON);

	i2c->busy = false;
	i2c->state = STATE_IDLE;

	/* signal rk3x_i2c_xfer that we are finished */
	wake_up(&i2c->wait);
}