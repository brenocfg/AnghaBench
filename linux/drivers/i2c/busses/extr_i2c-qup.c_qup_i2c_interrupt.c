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
struct qup_i2c_block {scalar_t__ is_tx_blk_mode; int /*<<< orphan*/  rx_bytes_read; int /*<<< orphan*/  fifo_available; int /*<<< orphan*/  is_rx_blk_mode; int /*<<< orphan*/  tx_fifo_free; } ;
struct qup_i2c_dev {int qup_err; int bus_err; int /*<<< orphan*/  xfer; TYPE_1__* msg; int /*<<< orphan*/  (* read_rx_fifo ) (struct qup_i2c_dev*) ;scalar_t__ in_blk_sz; scalar_t__ in_fifo_sz; scalar_t__ base; int /*<<< orphan*/  (* write_tx_fifo ) (struct qup_i2c_dev*) ;int /*<<< orphan*/  (* write_rx_tags ) (struct qup_i2c_dev*) ;scalar_t__ out_blk_sz; scalar_t__ use_dma; struct qup_i2c_block blk; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int I2C_STATUS_ERROR_MASK ; 
 int IN_BLOCK_READ_REQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int OUT_BLOCK_WRITE_REQ ; 
 scalar_t__ QUP_ERROR_FLAGS ; 
 scalar_t__ QUP_I2C_STATUS ; 
 int QUP_IN_SVC_FLAG ; 
 int QUP_MX_OUTPUT_DONE ; 
 scalar_t__ QUP_OPERATIONAL ; 
 int QUP_OUT_SVC_FLAG ; 
 int QUP_RESET_STATE ; 
 scalar_t__ QUP_STATE ; 
 int QUP_STATUS_ERROR_FLAGS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct qup_i2c_dev*) ; 
 int /*<<< orphan*/  stub2 (struct qup_i2c_dev*) ; 
 int /*<<< orphan*/  stub3 (struct qup_i2c_dev*) ; 
 int /*<<< orphan*/  stub4 (struct qup_i2c_dev*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t qup_i2c_interrupt(int irq, void *dev)
{
	struct qup_i2c_dev *qup = dev;
	struct qup_i2c_block *blk = &qup->blk;
	u32 bus_err;
	u32 qup_err;
	u32 opflags;

	bus_err = readl(qup->base + QUP_I2C_STATUS);
	qup_err = readl(qup->base + QUP_ERROR_FLAGS);
	opflags = readl(qup->base + QUP_OPERATIONAL);

	if (!qup->msg) {
		/* Clear Error interrupt */
		writel(QUP_RESET_STATE, qup->base + QUP_STATE);
		return IRQ_HANDLED;
	}

	bus_err &= I2C_STATUS_ERROR_MASK;
	qup_err &= QUP_STATUS_ERROR_FLAGS;

	/* Clear the error bits in QUP_ERROR_FLAGS */
	if (qup_err)
		writel(qup_err, qup->base + QUP_ERROR_FLAGS);

	/* Clear the error bits in QUP_I2C_STATUS */
	if (bus_err)
		writel(bus_err, qup->base + QUP_I2C_STATUS);

	/*
	 * Check for BAM mode and returns if already error has come for current
	 * transfer. In Error case, sometimes, QUP generates more than one
	 * interrupt.
	 */
	if (qup->use_dma && (qup->qup_err || qup->bus_err))
		return IRQ_HANDLED;

	/* Reset the QUP State in case of error */
	if (qup_err || bus_err) {
		/*
		 * Don’t reset the QUP state in case of BAM mode. The BAM
		 * flush operation needs to be scheduled in transfer function
		 * which will clear the remaining schedule descriptors in BAM
		 * HW FIFO and generates the BAM interrupt.
		 */
		if (!qup->use_dma)
			writel(QUP_RESET_STATE, qup->base + QUP_STATE);
		goto done;
	}

	if (opflags & QUP_OUT_SVC_FLAG) {
		writel(QUP_OUT_SVC_FLAG, qup->base + QUP_OPERATIONAL);

		if (opflags & OUT_BLOCK_WRITE_REQ) {
			blk->tx_fifo_free += qup->out_blk_sz;
			if (qup->msg->flags & I2C_M_RD)
				qup->write_rx_tags(qup);
			else
				qup->write_tx_fifo(qup);
		}
	}

	if (opflags & QUP_IN_SVC_FLAG) {
		writel(QUP_IN_SVC_FLAG, qup->base + QUP_OPERATIONAL);

		if (!blk->is_rx_blk_mode) {
			blk->fifo_available += qup->in_fifo_sz;
			qup->read_rx_fifo(qup);
		} else if (opflags & IN_BLOCK_READ_REQ) {
			blk->fifo_available += qup->in_blk_sz;
			qup->read_rx_fifo(qup);
		}
	}

	if (qup->msg->flags & I2C_M_RD) {
		if (!blk->rx_bytes_read)
			return IRQ_HANDLED;
	} else {
		/*
		 * Ideally, QUP_MAX_OUTPUT_DONE_FLAG should be checked
		 * for FIFO mode also. But, QUP_MAX_OUTPUT_DONE_FLAG lags
		 * behind QUP_OUTPUT_SERVICE_FLAG sometimes. The only reason
		 * of interrupt for write message in FIFO mode is
		 * QUP_MAX_OUTPUT_DONE_FLAG condition.
		 */
		if (blk->is_tx_blk_mode && !(opflags & QUP_MX_OUTPUT_DONE))
			return IRQ_HANDLED;
	}

done:
	qup->qup_err = qup_err;
	qup->bus_err = bus_err;
	complete(&qup->xfer);
	return IRQ_HANDLED;
}