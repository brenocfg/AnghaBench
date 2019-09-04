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
struct xlp9xx_i2c_dev {int msg_err; scalar_t__ msg_len; int /*<<< orphan*/  msg_complete; scalar_t__ msg_buf_remaining; int /*<<< orphan*/  msg_read; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  XLP9XX_I2C_INTEN ; 
 int XLP9XX_I2C_INTEN_DATADONE ; 
 int XLP9XX_I2C_INTEN_MFIFOEMTY ; 
 int XLP9XX_I2C_INTEN_MFIFOHI ; 
 int XLP9XX_I2C_INTEN_SADDR ; 
 int /*<<< orphan*/  XLP9XX_I2C_INTST ; 
 int XLP9XX_I2C_STATUS_ERRMASK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlp9xx_i2c_drain_rx_fifo (struct xlp9xx_i2c_dev*) ; 
 int /*<<< orphan*/  xlp9xx_i2c_fill_tx_fifo (struct xlp9xx_i2c_dev*) ; 
 int /*<<< orphan*/  xlp9xx_i2c_mask_irq (struct xlp9xx_i2c_dev*,int) ; 
 int xlp9xx_read_i2c_reg (struct xlp9xx_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp9xx_write_i2c_reg (struct xlp9xx_i2c_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t xlp9xx_i2c_isr(int irq, void *dev_id)
{
	struct xlp9xx_i2c_dev *priv = dev_id;
	u32 status;

	status = xlp9xx_read_i2c_reg(priv, XLP9XX_I2C_INTST);
	if (status == 0)
		return IRQ_NONE;

	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_INTST, status);
	if (status & XLP9XX_I2C_STATUS_ERRMASK) {
		priv->msg_err = status;
		goto xfer_done;
	}

	/* SADDR ACK for SMBUS_QUICK */
	if ((status & XLP9XX_I2C_INTEN_SADDR) && (priv->msg_len == 0))
		goto xfer_done;

	if (!priv->msg_read) {
		if (status & XLP9XX_I2C_INTEN_MFIFOEMTY) {
			/* TX FIFO got empty, fill it up again */
			if (priv->msg_buf_remaining)
				xlp9xx_i2c_fill_tx_fifo(priv);
			else
				xlp9xx_i2c_mask_irq(priv,
						    XLP9XX_I2C_INTEN_MFIFOEMTY);
		}
	} else {
		if (status & (XLP9XX_I2C_INTEN_DATADONE |
			      XLP9XX_I2C_INTEN_MFIFOHI)) {
			/* data is in FIFO, read it */
			if (priv->msg_buf_remaining)
				xlp9xx_i2c_drain_rx_fifo(priv);
		}
	}

	/* Transfer complete */
	if (status & XLP9XX_I2C_INTEN_DATADONE)
		goto xfer_done;

	return IRQ_HANDLED;

xfer_done:
	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_INTEN, 0);
	complete(&priv->msg_complete);
	return IRQ_HANDLED;
}