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
typedef  unsigned int u32 ;
struct i2c_msg {unsigned int len; } ;
struct axxia_i2c_dev {int last; int msg_err; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  msg_complete; scalar_t__ msg_xfrd_r; scalar_t__ msg_xfrd; struct i2c_msg* msg_r; struct i2c_msg* msg; } ;

/* Variables and functions */
 unsigned int CMD_AUTO ; 
 int CMD_BUSY ; 
 unsigned int CMD_MANUAL ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 unsigned int I2C_SMBUS_BLOCK_MAX ; 
 int /*<<< orphan*/  I2C_XFER_TIMEOUT ; 
 scalar_t__ MST_COMMAND ; 
 scalar_t__ MST_RX_XFER ; 
 unsigned int MST_STATUS_ERR ; 
 unsigned int MST_STATUS_RFL ; 
 unsigned int MST_STATUS_SNS ; 
 unsigned int MST_STATUS_SS ; 
 unsigned int MST_STATUS_TFL ; 
 scalar_t__ MST_TX_XFER ; 
 scalar_t__ WAIT_TIMER_CONTROL ; 
 unsigned int WT_EN ; 
 unsigned int WT_VALUE (int) ; 
 scalar_t__ axxia_i2c_fill_tx_fifo (struct axxia_i2c_dev*) ; 
 int /*<<< orphan*/  axxia_i2c_init (struct axxia_i2c_dev*) ; 
 int /*<<< orphan*/  axxia_i2c_set_addr (struct axxia_i2c_dev*,struct i2c_msg*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_int_disable (struct axxia_i2c_dev*,unsigned int) ; 
 int /*<<< orphan*/  i2c_int_enable (struct axxia_i2c_dev*,unsigned int) ; 
 scalar_t__ i2c_m_rd (struct i2c_msg*) ; 
 scalar_t__ i2c_m_recv_len (struct i2c_msg*) ; 
 int /*<<< orphan*/  i2c_recover_bus (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int axxia_i2c_xfer_msg(struct axxia_i2c_dev *idev, struct i2c_msg *msg,
			      bool last)
{
	u32 int_mask = MST_STATUS_ERR;
	u32 rx_xfer, tx_xfer;
	unsigned long time_left;
	unsigned int wt_value;

	idev->msg = msg;
	idev->msg_r = msg;
	idev->msg_xfrd = 0;
	idev->msg_xfrd_r = 0;
	idev->last = last;
	reinit_completion(&idev->msg_complete);

	axxia_i2c_set_addr(idev, msg);

	if (i2c_m_rd(msg)) {
		/* I2C read transfer */
		rx_xfer = i2c_m_recv_len(msg) ? I2C_SMBUS_BLOCK_MAX : msg->len;
		tx_xfer = 0;
	} else {
		/* I2C write transfer */
		rx_xfer = 0;
		tx_xfer = msg->len;
	}

	writel(rx_xfer, idev->base + MST_RX_XFER);
	writel(tx_xfer, idev->base + MST_TX_XFER);

	if (i2c_m_rd(msg))
		int_mask |= MST_STATUS_RFL;
	else if (axxia_i2c_fill_tx_fifo(idev) != 0)
		int_mask |= MST_STATUS_TFL;

	wt_value = WT_VALUE(readl(idev->base + WAIT_TIMER_CONTROL));
	/* Disable wait timer temporarly */
	writel(wt_value, idev->base + WAIT_TIMER_CONTROL);
	/* Check if timeout error happened */
	if (idev->msg_err)
		goto out;

	if (!last) {
		writel(CMD_MANUAL, idev->base + MST_COMMAND);
		int_mask |= MST_STATUS_SNS;
	} else {
		writel(CMD_AUTO, idev->base + MST_COMMAND);
		int_mask |= MST_STATUS_SS;
	}

	writel(WT_EN | wt_value, idev->base + WAIT_TIMER_CONTROL);

	i2c_int_enable(idev, int_mask);

	time_left = wait_for_completion_timeout(&idev->msg_complete,
					      I2C_XFER_TIMEOUT);

	i2c_int_disable(idev, int_mask);

	if (readl(idev->base + MST_COMMAND) & CMD_BUSY)
		dev_warn(idev->dev, "busy after xfer\n");

	if (time_left == 0) {
		idev->msg_err = -ETIMEDOUT;
		i2c_recover_bus(&idev->adapter);
		axxia_i2c_init(idev);
	}

out:
	if (unlikely(idev->msg_err) && idev->msg_err != -ENXIO &&
			idev->msg_err != -ETIMEDOUT)
		axxia_i2c_init(idev);

	return idev->msg_err;
}