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
struct i2c_msg {int addr; int len; } ;
struct axxia_i2c_dev {int msg_err; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  msg_complete; scalar_t__ msg_xfrd; struct i2c_msg* msg; } ;

/* Variables and functions */
 int CMD_BUSY ; 
 unsigned int CMD_MANUAL ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 int /*<<< orphan*/  I2C_XFER_TIMEOUT ; 
 scalar_t__ MST_ADDR_1 ; 
 scalar_t__ MST_ADDR_2 ; 
 scalar_t__ MST_COMMAND ; 
 scalar_t__ MST_RX_XFER ; 
 int MST_STATUS_ERR ; 
 int MST_STATUS_RFL ; 
 int MST_STATUS_SNS ; 
 int MST_STATUS_TFL ; 
 scalar_t__ MST_TX_XFER ; 
 scalar_t__ WAIT_TIMER_CONTROL ; 
 unsigned int WT_EN ; 
 unsigned int WT_VALUE (int) ; 
 scalar_t__ axxia_i2c_fill_tx_fifo (struct axxia_i2c_dev*) ; 
 int /*<<< orphan*/  axxia_i2c_init (struct axxia_i2c_dev*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int /*<<< orphan*/  i2c_int_disable (struct axxia_i2c_dev*,int) ; 
 int /*<<< orphan*/  i2c_int_enable (struct axxia_i2c_dev*,int) ; 
 scalar_t__ i2c_m_rd (struct i2c_msg*) ; 
 scalar_t__ i2c_m_recv_len (struct i2c_msg*) ; 
 scalar_t__ i2c_m_ten (struct i2c_msg*) ; 
 int /*<<< orphan*/  i2c_recover_bus (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int axxia_i2c_xfer_msg(struct axxia_i2c_dev *idev, struct i2c_msg *msg)
{
	u32 int_mask = MST_STATUS_ERR | MST_STATUS_SNS;
	u32 rx_xfer, tx_xfer;
	u32 addr_1, addr_2;
	unsigned long time_left;
	unsigned int wt_value;

	idev->msg = msg;
	idev->msg_xfrd = 0;
	reinit_completion(&idev->msg_complete);

	if (i2c_m_ten(msg)) {
		/* 10-bit address
		 *   addr_1: 5'b11110 | addr[9:8] | (R/nW)
		 *   addr_2: addr[7:0]
		 */
		addr_1 = 0xF0 | ((msg->addr >> 7) & 0x06);
		if (i2c_m_rd(msg))
			addr_1 |= 1;	/* Set the R/nW bit of the address */
		addr_2 = msg->addr & 0xFF;
	} else {
		/* 7-bit address
		 *   addr_1: addr[6:0] | (R/nW)
		 *   addr_2: dont care
		 */
		addr_1 = i2c_8bit_addr_from_msg(msg);
		addr_2 = 0;
	}

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
	writel(addr_1, idev->base + MST_ADDR_1);
	writel(addr_2, idev->base + MST_ADDR_2);

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

	/* Start manual mode */
	writel(CMD_MANUAL, idev->base + MST_COMMAND);

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