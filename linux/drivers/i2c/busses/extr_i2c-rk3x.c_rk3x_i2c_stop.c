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
struct rk3x_i2c {int error; int busy; int /*<<< orphan*/  wait; int /*<<< orphan*/  state; scalar_t__ is_last_msg; int /*<<< orphan*/ * msg; scalar_t__ processed; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CON ; 
 unsigned int REG_CON_STOP ; 
 unsigned int REG_CON_TUNING_MASK ; 
 int /*<<< orphan*/  REG_IEN ; 
 unsigned int REG_INT_STOP ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  STATE_STOP ; 
 unsigned int i2c_readl (struct rk3x_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_writel (struct rk3x_i2c*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rk3x_i2c_stop(struct rk3x_i2c *i2c, int error)
{
	unsigned int ctrl;

	i2c->processed = 0;
	i2c->msg = NULL;
	i2c->error = error;

	if (i2c->is_last_msg) {
		/* Enable stop interrupt */
		i2c_writel(i2c, REG_INT_STOP, REG_IEN);

		i2c->state = STATE_STOP;

		ctrl = i2c_readl(i2c, REG_CON);
		ctrl |= REG_CON_STOP;
		i2c_writel(i2c, ctrl, REG_CON);
	} else {
		/* Signal rk3x_i2c_xfer to start the next message. */
		i2c->busy = false;
		i2c->state = STATE_IDLE;

		/*
		 * The HW is actually not capable of REPEATED START. But we can
		 * get the intended effect by resetting its internal state
		 * and issuing an ordinary START.
		 */
		ctrl = i2c_readl(i2c, REG_CON) & REG_CON_TUNING_MASK;
		i2c_writel(i2c, ctrl, REG_CON);

		/* signal that we are finished with the current msg */
		wake_up(&i2c->wait);
	}
}