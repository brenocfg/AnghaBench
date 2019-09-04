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
struct drm_dp_aux_msg {int* buffer; int size; int request; int /*<<< orphan*/  reply; int /*<<< orphan*/  address; } ;
struct analogix_dp_device {scalar_t__ reg_base; int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ADDR_ONLY ; 
 scalar_t__ ANALOGIX_DP_AUX_ADDR_15_8 ; 
 scalar_t__ ANALOGIX_DP_AUX_ADDR_19_16 ; 
 scalar_t__ ANALOGIX_DP_AUX_ADDR_7_0 ; 
 scalar_t__ ANALOGIX_DP_AUX_CH_CTL_1 ; 
 scalar_t__ ANALOGIX_DP_AUX_CH_CTL_2 ; 
 scalar_t__ ANALOGIX_DP_AUX_CH_STA ; 
 scalar_t__ ANALOGIX_DP_AUX_RX_COMM ; 
 scalar_t__ ANALOGIX_DP_BUFFER_DATA_CTL ; 
 scalar_t__ ANALOGIX_DP_BUF_DATA_0 ; 
 scalar_t__ ANALOGIX_DP_INT_STA ; 
 int AUX_ADDR_15_8 (int /*<<< orphan*/ ) ; 
 int AUX_ADDR_19_16 (int /*<<< orphan*/ ) ; 
 int AUX_ADDR_7_0 (int /*<<< orphan*/ ) ; 
 int AUX_EN ; 
 int AUX_ERR ; 
 int AUX_LENGTH (int) ; 
 int AUX_RX_COMM_AUX_DEFER ; 
 int AUX_RX_COMM_I2C_DEFER ; 
 int AUX_STATUS_MASK ; 
 int AUX_TX_COMM_DP_TRANSACTION ; 
 int AUX_TX_COMM_I2C_TRANSACTION ; 
 int AUX_TX_COMM_MOT ; 
 int AUX_TX_COMM_READ ; 
 int AUX_TX_COMM_WRITE ; 
 int BUF_CLR ; 
 int DP_AUX_I2C_MOT ; 
#define  DP_AUX_I2C_READ 131 
 int /*<<< orphan*/  DP_AUX_I2C_REPLY_ACK ; 
 int /*<<< orphan*/  DP_AUX_I2C_REPLY_DEFER ; 
#define  DP_AUX_I2C_WRITE 130 
#define  DP_AUX_NATIVE_READ 129 
 int /*<<< orphan*/  DP_AUX_NATIVE_REPLY_ACK ; 
 int /*<<< orphan*/  DP_AUX_NATIVE_REPLY_DEFER ; 
#define  DP_AUX_NATIVE_WRITE 128 
 int E2BIG ; 
 int EBUSY ; 
 int EINVAL ; 
 int EREMOTEIO ; 
 int RPLY_RECEIV ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  analogix_dp_init_aux (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int readl (scalar_t__) ; 
 int readx_poll_timeout (int (*) (scalar_t__),scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

ssize_t analogix_dp_transfer(struct analogix_dp_device *dp,
			     struct drm_dp_aux_msg *msg)
{
	u32 reg;
	u32 status_reg;
	u8 *buffer = msg->buffer;
	unsigned int i;
	int num_transferred = 0;
	int ret;

	/* Buffer size of AUX CH is 16 bytes */
	if (WARN_ON(msg->size > 16))
		return -E2BIG;

	/* Clear AUX CH data buffer */
	reg = BUF_CLR;
	writel(reg, dp->reg_base + ANALOGIX_DP_BUFFER_DATA_CTL);

	switch (msg->request & ~DP_AUX_I2C_MOT) {
	case DP_AUX_I2C_WRITE:
		reg = AUX_TX_COMM_WRITE | AUX_TX_COMM_I2C_TRANSACTION;
		if (msg->request & DP_AUX_I2C_MOT)
			reg |= AUX_TX_COMM_MOT;
		break;

	case DP_AUX_I2C_READ:
		reg = AUX_TX_COMM_READ | AUX_TX_COMM_I2C_TRANSACTION;
		if (msg->request & DP_AUX_I2C_MOT)
			reg |= AUX_TX_COMM_MOT;
		break;

	case DP_AUX_NATIVE_WRITE:
		reg = AUX_TX_COMM_WRITE | AUX_TX_COMM_DP_TRANSACTION;
		break;

	case DP_AUX_NATIVE_READ:
		reg = AUX_TX_COMM_READ | AUX_TX_COMM_DP_TRANSACTION;
		break;

	default:
		return -EINVAL;
	}

	reg |= AUX_LENGTH(msg->size);
	writel(reg, dp->reg_base + ANALOGIX_DP_AUX_CH_CTL_1);

	/* Select DPCD device address */
	reg = AUX_ADDR_7_0(msg->address);
	writel(reg, dp->reg_base + ANALOGIX_DP_AUX_ADDR_7_0);
	reg = AUX_ADDR_15_8(msg->address);
	writel(reg, dp->reg_base + ANALOGIX_DP_AUX_ADDR_15_8);
	reg = AUX_ADDR_19_16(msg->address);
	writel(reg, dp->reg_base + ANALOGIX_DP_AUX_ADDR_19_16);

	if (!(msg->request & DP_AUX_I2C_READ)) {
		for (i = 0; i < msg->size; i++) {
			reg = buffer[i];
			writel(reg, dp->reg_base + ANALOGIX_DP_BUF_DATA_0 +
			       4 * i);
			num_transferred++;
		}
	}

	/* Enable AUX CH operation */
	reg = AUX_EN;

	/* Zero-sized messages specify address-only transactions. */
	if (msg->size < 1)
		reg |= ADDR_ONLY;

	writel(reg, dp->reg_base + ANALOGIX_DP_AUX_CH_CTL_2);

	ret = readx_poll_timeout(readl, dp->reg_base + ANALOGIX_DP_AUX_CH_CTL_2,
				 reg, !(reg & AUX_EN), 25, 500 * 1000);
	if (ret) {
		dev_err(dp->dev, "AUX CH enable timeout!\n");
		goto aux_error;
	}

	/* TODO: Wait for an interrupt instead of looping? */
	/* Is AUX CH command reply received? */
	ret = readx_poll_timeout(readl, dp->reg_base + ANALOGIX_DP_INT_STA,
				 reg, reg & RPLY_RECEIV, 10, 20 * 1000);
	if (ret) {
		dev_err(dp->dev, "AUX CH cmd reply timeout!\n");
		goto aux_error;
	}

	/* Clear interrupt source for AUX CH command reply */
	writel(RPLY_RECEIV, dp->reg_base + ANALOGIX_DP_INT_STA);

	/* Clear interrupt source for AUX CH access error */
	reg = readl(dp->reg_base + ANALOGIX_DP_INT_STA);
	status_reg = readl(dp->reg_base + ANALOGIX_DP_AUX_CH_STA);
	if ((reg & AUX_ERR) || (status_reg & AUX_STATUS_MASK)) {
		writel(AUX_ERR, dp->reg_base + ANALOGIX_DP_INT_STA);

		dev_warn(dp->dev, "AUX CH error happened: %#x (%d)\n",
			 status_reg & AUX_STATUS_MASK, !!(reg & AUX_ERR));
		goto aux_error;
	}

	if (msg->request & DP_AUX_I2C_READ) {
		for (i = 0; i < msg->size; i++) {
			reg = readl(dp->reg_base + ANALOGIX_DP_BUF_DATA_0 +
				    4 * i);
			buffer[i] = (unsigned char)reg;
			num_transferred++;
		}
	}

	/* Check if Rx sends defer */
	reg = readl(dp->reg_base + ANALOGIX_DP_AUX_RX_COMM);
	if (reg == AUX_RX_COMM_AUX_DEFER)
		msg->reply = DP_AUX_NATIVE_REPLY_DEFER;
	else if (reg == AUX_RX_COMM_I2C_DEFER)
		msg->reply = DP_AUX_I2C_REPLY_DEFER;
	else if ((msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_I2C_WRITE ||
		 (msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_I2C_READ)
		msg->reply = DP_AUX_I2C_REPLY_ACK;
	else if ((msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_NATIVE_WRITE ||
		 (msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_NATIVE_READ)
		msg->reply = DP_AUX_NATIVE_REPLY_ACK;

	return num_transferred > 0 ? num_transferred : -EBUSY;

aux_error:
	/* if aux err happen, reset aux */
	analogix_dp_init_aux(dp);

	return -EREMOTEIO;
}