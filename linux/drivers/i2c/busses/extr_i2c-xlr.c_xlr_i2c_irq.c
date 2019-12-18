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
struct xlr_i2c_private {scalar_t__ pos; int /*<<< orphan*/  wait; int /*<<< orphan*/  iobase; struct i2c_msg* msg; } ;
struct i2c_msg {scalar_t__ len; int flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int I2C_M_RD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  XLR_I2C_INT_STAT ; 
 int /*<<< orphan*/  XLR_I2C_STATUS ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlr_i2c_busy (struct xlr_i2c_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_i2c_rdreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_i2c_rx_irq (struct xlr_i2c_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_i2c_tx_irq (struct xlr_i2c_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_i2c_wreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t xlr_i2c_irq(int irq, void *dev_id)
{
	struct xlr_i2c_private *priv = dev_id;
	struct i2c_msg *msg = priv->msg;
	u32 int_stat, status;

	int_stat = xlr_i2c_rdreg(priv->iobase, XLR_I2C_INT_STAT);
	if (!int_stat)
		return IRQ_NONE;

	xlr_i2c_wreg(priv->iobase, XLR_I2C_INT_STAT, int_stat);

	if (!msg)
		return IRQ_HANDLED;

	status = xlr_i2c_rdreg(priv->iobase, XLR_I2C_STATUS);

	if (priv->pos < msg->len) {
		if (msg->flags & I2C_M_RD)
			xlr_i2c_rx_irq(priv, status);
		else
			xlr_i2c_tx_irq(priv, status);
	}

	if (!xlr_i2c_busy(priv, status))
		wake_up(&priv->wait);

	return IRQ_HANDLED;
}