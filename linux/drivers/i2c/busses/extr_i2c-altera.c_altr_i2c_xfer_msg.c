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
typedef  int u8 ;
typedef  int u32 ;
struct i2c_msg {int flags; int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct altr_i2c_dev {int msg_err; int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  msg_complete; int /*<<< orphan*/  buf; int /*<<< orphan*/  msg_len; struct i2c_msg* msg; } ;

/* Variables and functions */
 int ALTR_I2C_ISER_RXOF_EN ; 
 int ALTR_I2C_ISER_RXRDY_EN ; 
 int ALTR_I2C_ISR_ARB ; 
 int ALTR_I2C_ISR_NACK ; 
 int ALTR_I2C_ISR_RXOF ; 
 int ALTR_I2C_ISR_TXRDY ; 
 scalar_t__ ALTR_I2C_RX_DATA ; 
 scalar_t__ ALTR_I2C_RX_FIFO_LVL ; 
 scalar_t__ ALTR_I2C_STATUS ; 
 int ALTR_I2C_STAT_CORE ; 
 scalar_t__ ALTR_I2C_TFR_CMD ; 
 int ALTR_I2C_TFR_CMD_STA ; 
 int /*<<< orphan*/  ALTR_I2C_XFER_TIMEOUT ; 
 int ETIMEDOUT ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  altr_i2c_core_disable (struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  altr_i2c_core_enable (struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  altr_i2c_fill_tx_fifo (struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  altr_i2c_int_enable (struct altr_i2c_dev*,int,int) ; 
 int /*<<< orphan*/  altr_i2c_transfer (struct altr_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int altr_i2c_xfer_msg(struct altr_i2c_dev *idev, struct i2c_msg *msg)
{
	u32 imask = ALTR_I2C_ISR_RXOF | ALTR_I2C_ISR_ARB | ALTR_I2C_ISR_NACK;
	unsigned long time_left;
	u32 value;
	u8 addr = i2c_8bit_addr_from_msg(msg);

	idev->msg = msg;
	idev->msg_len = msg->len;
	idev->buf = msg->buf;
	idev->msg_err = 0;
	reinit_completion(&idev->msg_complete);
	altr_i2c_core_enable(idev);

	/* Make sure RX FIFO is empty */
	do {
		readl(idev->base + ALTR_I2C_RX_DATA);
	} while (readl(idev->base + ALTR_I2C_RX_FIFO_LVL));

	writel(ALTR_I2C_TFR_CMD_STA | addr, idev->base + ALTR_I2C_TFR_CMD);

	if ((msg->flags & I2C_M_RD) != 0) {
		imask |= ALTR_I2C_ISER_RXOF_EN | ALTR_I2C_ISER_RXRDY_EN;
		altr_i2c_int_enable(idev, imask, true);
		/* write the first byte to start the RX */
		altr_i2c_transfer(idev, 0);
	} else {
		imask |= ALTR_I2C_ISR_TXRDY;
		altr_i2c_int_enable(idev, imask, true);
		altr_i2c_fill_tx_fifo(idev);
	}

	time_left = wait_for_completion_timeout(&idev->msg_complete,
						ALTR_I2C_XFER_TIMEOUT);
	altr_i2c_int_enable(idev, imask, false);

	value = readl(idev->base + ALTR_I2C_STATUS) & ALTR_I2C_STAT_CORE;
	if (value)
		dev_err(idev->dev, "Core Status not IDLE...\n");

	if (time_left == 0) {
		idev->msg_err = -ETIMEDOUT;
		dev_dbg(idev->dev, "Transaction timed out.\n");
	}

	altr_i2c_core_disable(idev);

	return idev->msg_err;
}