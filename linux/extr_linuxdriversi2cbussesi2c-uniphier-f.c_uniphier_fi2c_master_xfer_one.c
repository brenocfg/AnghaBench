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
struct uniphier_fi2c_priv {int error; int flags; scalar_t__ membase; int /*<<< orphan*/  comp; int /*<<< orphan*/  enabled_irqs; int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int I2C_M_RD ; 
 scalar_t__ UNIPHIER_FI2C_CR ; 
 int UNIPHIER_FI2C_CR_MST ; 
 int UNIPHIER_FI2C_CR_STA ; 
 int UNIPHIER_FI2C_DEFER_STOP_COMP ; 
 int /*<<< orphan*/  UNIPHIER_FI2C_INT_FAULTS ; 
 scalar_t__ UNIPHIER_FI2C_RST ; 
 int UNIPHIER_FI2C_RST_RBRST ; 
 int UNIPHIER_FI2C_RST_TBRST ; 
 scalar_t__ UNIPHIER_FI2C_SR ; 
 int UNIPHIER_FI2C_SR_BB ; 
 int UNIPHIER_FI2C_SR_STS ; 
 int UNIPHIER_FI2C_STOP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct uniphier_fi2c_priv* i2c_get_adapdata (struct i2c_adapter*) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uniphier_fi2c_clear_irqs (struct uniphier_fi2c_priv*) ; 
 int /*<<< orphan*/  uniphier_fi2c_recover (struct uniphier_fi2c_priv*) ; 
 int /*<<< orphan*/  uniphier_fi2c_rx_init (struct uniphier_fi2c_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_fi2c_set_irqs (struct uniphier_fi2c_priv*) ; 
 int /*<<< orphan*/  uniphier_fi2c_tx_init (struct uniphier_fi2c_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int uniphier_fi2c_master_xfer_one(struct i2c_adapter *adap,
					 struct i2c_msg *msg, bool stop)
{
	struct uniphier_fi2c_priv *priv = i2c_get_adapdata(adap);
	bool is_read = msg->flags & I2C_M_RD;
	unsigned long time_left;

	dev_dbg(&adap->dev, "%s: addr=0x%02x, len=%d, stop=%d\n",
		is_read ? "receive" : "transmit", msg->addr, msg->len, stop);

	priv->len = msg->len;
	priv->buf = msg->buf;
	priv->enabled_irqs = UNIPHIER_FI2C_INT_FAULTS;
	priv->error = 0;
	priv->flags = 0;

	if (stop)
		priv->flags |= UNIPHIER_FI2C_STOP;

	reinit_completion(&priv->comp);
	uniphier_fi2c_clear_irqs(priv);
	writel(UNIPHIER_FI2C_RST_TBRST | UNIPHIER_FI2C_RST_RBRST,
	       priv->membase + UNIPHIER_FI2C_RST);	/* reset TX/RX FIFO */

	if (is_read)
		uniphier_fi2c_rx_init(priv, msg->addr);
	else
		uniphier_fi2c_tx_init(priv, msg->addr);

	uniphier_fi2c_set_irqs(priv);

	dev_dbg(&adap->dev, "start condition\n");
	writel(UNIPHIER_FI2C_CR_MST | UNIPHIER_FI2C_CR_STA,
	       priv->membase + UNIPHIER_FI2C_CR);

	time_left = wait_for_completion_timeout(&priv->comp, adap->timeout);
	if (!time_left) {
		dev_err(&adap->dev, "transaction timeout.\n");
		uniphier_fi2c_recover(priv);
		return -ETIMEDOUT;
	}
	dev_dbg(&adap->dev, "complete\n");

	if (unlikely(priv->flags & UNIPHIER_FI2C_DEFER_STOP_COMP)) {
		u32 status;
		int ret;

		ret = readl_poll_timeout(priv->membase + UNIPHIER_FI2C_SR,
					 status,
					 (status & UNIPHIER_FI2C_SR_STS) &&
					 !(status & UNIPHIER_FI2C_SR_BB),
					 1, 20);
		if (ret) {
			dev_err(&adap->dev,
				"stop condition was not completed.\n");
			uniphier_fi2c_recover(priv);
			return ret;
		}
	}

	return priv->error;
}