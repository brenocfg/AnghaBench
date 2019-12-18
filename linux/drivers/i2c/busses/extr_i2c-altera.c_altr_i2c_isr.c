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
typedef  int u32 ;
struct altr_i2c_dev {int isr_status; scalar_t__ msg_len; int /*<<< orphan*/  dev; int /*<<< orphan*/  msg_complete; scalar_t__ base; int /*<<< orphan*/  msg_err; TYPE_1__* msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ALTR_I2C_ALL_IRQ ; 
 int ALTR_I2C_ISR_ARB ; 
 int ALTR_I2C_ISR_NACK ; 
 int ALTR_I2C_ISR_RXOF ; 
 int ALTR_I2C_ISR_RXRDY ; 
 int ALTR_I2C_ISR_TXRDY ; 
 scalar_t__ ALTR_I2C_STATUS ; 
 int ALTR_I2C_STAT_CORE ; 
 int /*<<< orphan*/  ALTR_I2C_TIMEOUT ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENXIO ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  altr_i2c_empty_rx_fifo (struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  altr_i2c_fill_tx_fifo (struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  altr_i2c_int_clear (struct altr_i2c_dev*,int) ; 
 int /*<<< orphan*/  altr_i2c_int_enable (struct altr_i2c_dev*,int,int) ; 
 int /*<<< orphan*/  altr_i2c_stop (struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int readl_poll_timeout_atomic (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t altr_i2c_isr(int irq, void *_dev)
{
	int ret;
	bool read, finish = false;
	struct altr_i2c_dev *idev = _dev;
	u32 status = idev->isr_status;

	if (!idev->msg) {
		dev_warn(idev->dev, "unexpected interrupt\n");
		altr_i2c_int_clear(idev, ALTR_I2C_ALL_IRQ);
		return IRQ_HANDLED;
	}
	read = (idev->msg->flags & I2C_M_RD) != 0;

	/* handle Lost Arbitration */
	if (unlikely(status & ALTR_I2C_ISR_ARB)) {
		altr_i2c_int_clear(idev, ALTR_I2C_ISR_ARB);
		idev->msg_err = -EAGAIN;
		finish = true;
	} else if (unlikely(status & ALTR_I2C_ISR_NACK)) {
		dev_dbg(idev->dev, "Could not get ACK\n");
		idev->msg_err = -ENXIO;
		altr_i2c_int_clear(idev, ALTR_I2C_ISR_NACK);
		altr_i2c_stop(idev);
		finish = true;
	} else if (read && unlikely(status & ALTR_I2C_ISR_RXOF)) {
		/* handle RX FIFO Overflow */
		altr_i2c_empty_rx_fifo(idev);
		altr_i2c_int_clear(idev, ALTR_I2C_ISR_RXRDY);
		altr_i2c_stop(idev);
		dev_err(idev->dev, "RX FIFO Overflow\n");
		finish = true;
	} else if (read && (status & ALTR_I2C_ISR_RXRDY)) {
		/* RX FIFO needs service? */
		altr_i2c_empty_rx_fifo(idev);
		altr_i2c_int_clear(idev, ALTR_I2C_ISR_RXRDY);
		if (!idev->msg_len)
			finish = true;
	} else if (!read && (status & ALTR_I2C_ISR_TXRDY)) {
		/* TX FIFO needs service? */
		altr_i2c_int_clear(idev, ALTR_I2C_ISR_TXRDY);
		if (idev->msg_len > 0)
			altr_i2c_fill_tx_fifo(idev);
		else
			finish = true;
	} else {
		dev_warn(idev->dev, "Unexpected interrupt: 0x%x\n", status);
		altr_i2c_int_clear(idev, ALTR_I2C_ALL_IRQ);
	}

	if (finish) {
		/* Wait for the Core to finish */
		ret = readl_poll_timeout_atomic(idev->base + ALTR_I2C_STATUS,
						status,
						!(status & ALTR_I2C_STAT_CORE),
						1, ALTR_I2C_TIMEOUT);
		if (ret)
			dev_err(idev->dev, "message timeout\n");
		altr_i2c_int_enable(idev, ALTR_I2C_ALL_IRQ, false);
		altr_i2c_int_clear(idev, ALTR_I2C_ALL_IRQ);
		complete(&idev->msg_complete);
		dev_dbg(idev->dev, "Message Complete\n");
	}

	return IRQ_HANDLED;
}