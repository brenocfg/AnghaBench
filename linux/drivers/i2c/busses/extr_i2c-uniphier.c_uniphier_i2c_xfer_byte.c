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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_i2c_priv {scalar_t__ membase; int /*<<< orphan*/  comp; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ UNIPHIER_I2C_DREC ; 
 scalar_t__ UNIPHIER_I2C_DTRM ; 
 int /*<<< orphan*/  UNIPHIER_I2C_DTRM_IRQEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct uniphier_i2c_priv* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int uniphier_i2c_xfer_byte(struct i2c_adapter *adap, u32 txdata,
				  u32 *rxdatap)
{
	struct uniphier_i2c_priv *priv = i2c_get_adapdata(adap);
	unsigned long time_left;
	u32 rxdata;

	reinit_completion(&priv->comp);

	txdata |= UNIPHIER_I2C_DTRM_IRQEN;
	writel(txdata, priv->membase + UNIPHIER_I2C_DTRM);

	time_left = wait_for_completion_timeout(&priv->comp, adap->timeout);
	if (unlikely(!time_left)) {
		dev_err(&adap->dev, "transaction timeout\n");
		return -ETIMEDOUT;
	}

	rxdata = readl(priv->membase + UNIPHIER_I2C_DREC);
	if (rxdatap)
		*rxdatap = rxdata;

	return 0;
}