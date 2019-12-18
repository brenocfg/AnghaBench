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
struct qup_i2c_block {int cur_data; int /*<<< orphan*/  tx_fifo_free; int /*<<< orphan*/  is_tx_blk_mode; } ;
struct qup_i2c_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  out_fifo_sz; int /*<<< orphan*/  xfer; scalar_t__ base; int /*<<< orphan*/  clk_ctl; int /*<<< orphan*/  config_run; scalar_t__ is_smbus_read; struct i2c_msg* msg; struct qup_i2c_block blk; } ;
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ QUP_I2C_CLK_CTL ; 
 int /*<<< orphan*/  QUP_I2C_MX_CONFIG_DURING_RUN ; 
 int /*<<< orphan*/  QUP_PAUSE_STATE ; 
 int /*<<< orphan*/  QUP_RUN_STATE ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int qup_i2c_change_state (struct qup_i2c_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ qup_i2c_check_msg_len (struct i2c_msg*) ; 
 int /*<<< orphan*/  qup_i2c_clear_blk_v2 (struct qup_i2c_block*) ; 
 int /*<<< orphan*/  qup_i2c_conf_count_v2 (struct qup_i2c_dev*) ; 
 int qup_i2c_wait_for_complete (struct qup_i2c_dev*,struct i2c_msg*) ; 
 int /*<<< orphan*/  qup_i2c_write_rx_tags_v2 (struct qup_i2c_dev*) ; 
 int /*<<< orphan*/  qup_i2c_write_tx_fifo_v2 (struct qup_i2c_dev*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
qup_i2c_conf_xfer_v2(struct qup_i2c_dev *qup, bool is_rx, bool is_first,
		     bool change_pause_state)
{
	struct qup_i2c_block *blk = &qup->blk;
	struct i2c_msg *msg = qup->msg;
	int ret;

	/*
	 * Check if its SMBus Block read for which the top level read will be
	 * done into 2 QUP reads. One with message length 1 while other one is
	 * with actual length.
	 */
	if (qup_i2c_check_msg_len(msg)) {
		if (qup->is_smbus_read) {
			/*
			 * If the message length is already read in
			 * the first byte of the buffer, account for
			 * that by setting the offset
			 */
			blk->cur_data += 1;
			is_first = false;
		} else {
			change_pause_state = false;
		}
	}

	qup->config_run = is_first ? 0 : QUP_I2C_MX_CONFIG_DURING_RUN;

	qup_i2c_clear_blk_v2(blk);
	qup_i2c_conf_count_v2(qup);

	/* If it is first sub transfer, then configure i2c bus clocks */
	if (is_first) {
		ret = qup_i2c_change_state(qup, QUP_RUN_STATE);
		if (ret)
			return ret;

		writel(qup->clk_ctl, qup->base + QUP_I2C_CLK_CTL);

		ret = qup_i2c_change_state(qup, QUP_PAUSE_STATE);
		if (ret)
			return ret;
	}

	reinit_completion(&qup->xfer);
	enable_irq(qup->irq);
	/*
	 * In FIFO mode, tx FIFO can be written directly while in block mode the
	 * it will be written after getting OUT_BLOCK_WRITE_REQ interrupt
	 */
	if (!blk->is_tx_blk_mode) {
		blk->tx_fifo_free = qup->out_fifo_sz;

		if (is_rx)
			qup_i2c_write_rx_tags_v2(qup);
		else
			qup_i2c_write_tx_fifo_v2(qup);
	}

	ret = qup_i2c_change_state(qup, QUP_RUN_STATE);
	if (ret)
		goto err;

	ret = qup_i2c_wait_for_complete(qup, msg);
	if (ret)
		goto err;

	/* Move to pause state for all the transfers, except last one */
	if (change_pause_state) {
		ret = qup_i2c_change_state(qup, QUP_PAUSE_STATE);
		if (ret)
			goto err;
	}

err:
	disable_irq(qup->irq);
	return ret;
}