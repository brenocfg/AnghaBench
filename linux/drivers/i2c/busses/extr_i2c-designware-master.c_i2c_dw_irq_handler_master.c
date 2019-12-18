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
struct dw_i2c_dev {int flags; int /*<<< orphan*/  cmd_complete; scalar_t__ msg_err; int /*<<< orphan*/  status; int /*<<< orphan*/  cmd_err; } ;

/* Variables and functions */
 int ACCESS_INTR_MASK ; 
 int /*<<< orphan*/  DW_IC_ERR_TX_ABRT ; 
 int /*<<< orphan*/  DW_IC_INTR_MASK ; 
 int DW_IC_INTR_RX_FULL ; 
 int DW_IC_INTR_STOP_DET ; 
 int DW_IC_INTR_TX_ABRT ; 
 int DW_IC_INTR_TX_EMPTY ; 
 int /*<<< orphan*/  STATUS_IDLE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_writel (struct dw_i2c_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_dw_disable_int (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_dw_read (struct dw_i2c_dev*) ; 
 int i2c_dw_read_clear_intrbits (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_dw_xfer_msg (struct dw_i2c_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int i2c_dw_irq_handler_master(struct dw_i2c_dev *dev)
{
	u32 stat;

	stat = i2c_dw_read_clear_intrbits(dev);
	if (stat & DW_IC_INTR_TX_ABRT) {
		dev->cmd_err |= DW_IC_ERR_TX_ABRT;
		dev->status = STATUS_IDLE;

		/*
		 * Anytime TX_ABRT is set, the contents of the tx/rx
		 * buffers are flushed. Make sure to skip them.
		 */
		dw_writel(dev, 0, DW_IC_INTR_MASK);
		goto tx_aborted;
	}

	if (stat & DW_IC_INTR_RX_FULL)
		i2c_dw_read(dev);

	if (stat & DW_IC_INTR_TX_EMPTY)
		i2c_dw_xfer_msg(dev);

	/*
	 * No need to modify or disable the interrupt mask here.
	 * i2c_dw_xfer_msg() will take care of it according to
	 * the current transmit status.
	 */

tx_aborted:
	if ((stat & (DW_IC_INTR_TX_ABRT | DW_IC_INTR_STOP_DET)) || dev->msg_err)
		complete(&dev->cmd_complete);
	else if (unlikely(dev->flags & ACCESS_INTR_MASK)) {
		/* Workaround to trigger pending interrupt */
		stat = dw_readl(dev, DW_IC_INTR_MASK);
		i2c_dw_disable_int(dev);
		dw_writel(dev, stat, DW_IC_INTR_MASK);
	}

	return 0;
}