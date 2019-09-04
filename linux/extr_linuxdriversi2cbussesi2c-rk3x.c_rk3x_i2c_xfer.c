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
typedef  int u32 ;
struct rk3x_i2c {int is_last_msg; int error; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  pclk; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; int /*<<< orphan*/  busy; int /*<<< orphan*/  wait; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {scalar_t__ algo_data; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_CON ; 
 int REG_CON_EN ; 
 int REG_CON_STOP ; 
 int REG_CON_TUNING_MASK ; 
 int /*<<< orphan*/  REG_IEN ; 
 int /*<<< orphan*/  REG_IPD ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  WAIT_TIMEOUT ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int i2c_readl (struct rk3x_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_writel (struct rk3x_i2c*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int rk3x_i2c_setup (struct rk3x_i2c*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  rk3x_i2c_start (struct rk3x_i2c*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk3x_i2c_xfer(struct i2c_adapter *adap,
			 struct i2c_msg *msgs, int num)
{
	struct rk3x_i2c *i2c = (struct rk3x_i2c *)adap->algo_data;
	unsigned long timeout, flags;
	u32 val;
	int ret = 0;
	int i;

	spin_lock_irqsave(&i2c->lock, flags);

	clk_enable(i2c->clk);
	clk_enable(i2c->pclk);

	i2c->is_last_msg = false;

	/*
	 * Process msgs. We can handle more than one message at once (see
	 * rk3x_i2c_setup()).
	 */
	for (i = 0; i < num; i += ret) {
		ret = rk3x_i2c_setup(i2c, msgs + i, num - i);

		if (ret < 0) {
			dev_err(i2c->dev, "rk3x_i2c_setup() failed\n");
			break;
		}

		if (i + ret >= num)
			i2c->is_last_msg = true;

		spin_unlock_irqrestore(&i2c->lock, flags);

		rk3x_i2c_start(i2c);

		timeout = wait_event_timeout(i2c->wait, !i2c->busy,
					     msecs_to_jiffies(WAIT_TIMEOUT));

		spin_lock_irqsave(&i2c->lock, flags);

		if (timeout == 0) {
			dev_err(i2c->dev, "timeout, ipd: 0x%02x, state: %d\n",
				i2c_readl(i2c, REG_IPD), i2c->state);

			/* Force a STOP condition without interrupt */
			i2c_writel(i2c, 0, REG_IEN);
			val = i2c_readl(i2c, REG_CON) & REG_CON_TUNING_MASK;
			val |= REG_CON_EN | REG_CON_STOP;
			i2c_writel(i2c, val, REG_CON);

			i2c->state = STATE_IDLE;

			ret = -ETIMEDOUT;
			break;
		}

		if (i2c->error) {
			ret = i2c->error;
			break;
		}
	}

	clk_disable(i2c->pclk);
	clk_disable(i2c->clk);

	spin_unlock_irqrestore(&i2c->lock, flags);

	return ret < 0 ? ret : num;
}