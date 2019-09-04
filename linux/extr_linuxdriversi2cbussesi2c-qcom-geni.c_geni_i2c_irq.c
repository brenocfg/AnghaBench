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
typedef  int /*<<< orphan*/  val ;
typedef  int u32 ;
struct i2c_msg {int flags; scalar_t__ len; int* buf; } ;
struct TYPE_2__ {scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct geni_i2c_dev {scalar_t__ cur_rd; int tx_wm; scalar_t__ cur_wr; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; TYPE_1__ se; struct i2c_msg* cur; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_LOST ; 
 int /*<<< orphan*/  BUS_PROTO ; 
 int DM_I2C_CB_ERR ; 
 int /*<<< orphan*/  GENI_ABORT_DONE ; 
 int /*<<< orphan*/  GENI_ILLEGAL_CMD ; 
 int /*<<< orphan*/  GENI_OVERRUN ; 
 int /*<<< orphan*/  GP_IRQ0 ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int M_CMD_ABORT_EN ; 
 int M_CMD_DONE_EN ; 
 int M_CMD_FAILURE_EN ; 
 int M_CMD_OVERRUN_EN ; 
 int M_GP_IRQ_0_EN ; 
 int M_GP_IRQ_1_EN ; 
 int M_GP_IRQ_3_EN ; 
 int M_GP_IRQ_4_EN ; 
 int M_ILLEGAL_CMD_EN ; 
 int M_RX_FIFO_LAST_EN ; 
 int M_RX_FIFO_WATERMARK_EN ; 
 int M_TX_FIFO_WATERMARK_EN ; 
 int /*<<< orphan*/  NACK ; 
 int RX_DMA_DONE ; 
 int RX_FIFO_WC_MSK ; 
 int RX_RESET_DONE ; 
 scalar_t__ SE_DMA_RX_IRQ_CLR ; 
 scalar_t__ SE_DMA_RX_IRQ_STAT ; 
 scalar_t__ SE_DMA_TX_IRQ_CLR ; 
 scalar_t__ SE_DMA_TX_IRQ_STAT ; 
 scalar_t__ SE_GENI_DMA_MODE_EN ; 
 scalar_t__ SE_GENI_M_IRQ_CLEAR ; 
 scalar_t__ SE_GENI_M_IRQ_STATUS ; 
 scalar_t__ SE_GENI_RX_FIFO_STATUS ; 
 scalar_t__ SE_GENI_RX_FIFOn ; 
 scalar_t__ SE_GENI_TX_FIFOn ; 
 scalar_t__ SE_GENI_TX_WATERMARK_REG ; 
 int TX_DMA_DONE ; 
 int TX_RESET_DONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  geni_i2c_err (struct geni_i2c_dev*,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t geni_i2c_irq(int irq, void *dev)
{
	struct geni_i2c_dev *gi2c = dev;
	int j;
	u32 m_stat;
	u32 rx_st;
	u32 dm_tx_st;
	u32 dm_rx_st;
	u32 dma;
	struct i2c_msg *cur;
	unsigned long flags;

	spin_lock_irqsave(&gi2c->lock, flags);
	m_stat = readl_relaxed(gi2c->se.base + SE_GENI_M_IRQ_STATUS);
	rx_st = readl_relaxed(gi2c->se.base + SE_GENI_RX_FIFO_STATUS);
	dm_tx_st = readl_relaxed(gi2c->se.base + SE_DMA_TX_IRQ_STAT);
	dm_rx_st = readl_relaxed(gi2c->se.base + SE_DMA_RX_IRQ_STAT);
	dma = readl_relaxed(gi2c->se.base + SE_GENI_DMA_MODE_EN);
	cur = gi2c->cur;

	if (!cur ||
	    m_stat & (M_CMD_FAILURE_EN | M_CMD_ABORT_EN) ||
	    dm_rx_st & (DM_I2C_CB_ERR)) {
		if (m_stat & M_GP_IRQ_1_EN)
			geni_i2c_err(gi2c, NACK);
		if (m_stat & M_GP_IRQ_3_EN)
			geni_i2c_err(gi2c, BUS_PROTO);
		if (m_stat & M_GP_IRQ_4_EN)
			geni_i2c_err(gi2c, ARB_LOST);
		if (m_stat & M_CMD_OVERRUN_EN)
			geni_i2c_err(gi2c, GENI_OVERRUN);
		if (m_stat & M_ILLEGAL_CMD_EN)
			geni_i2c_err(gi2c, GENI_ILLEGAL_CMD);
		if (m_stat & M_CMD_ABORT_EN)
			geni_i2c_err(gi2c, GENI_ABORT_DONE);
		if (m_stat & M_GP_IRQ_0_EN)
			geni_i2c_err(gi2c, GP_IRQ0);

		/* Disable the TX Watermark interrupt to stop TX */
		if (!dma)
			writel_relaxed(0, gi2c->se.base +
					   SE_GENI_TX_WATERMARK_REG);
		goto irqret;
	}

	if (dma) {
		dev_dbg(gi2c->se.dev, "i2c dma tx:0x%x, dma rx:0x%x\n",
			dm_tx_st, dm_rx_st);
		goto irqret;
	}

	if (cur->flags & I2C_M_RD &&
	    m_stat & (M_RX_FIFO_WATERMARK_EN | M_RX_FIFO_LAST_EN)) {
		u32 rxcnt = rx_st & RX_FIFO_WC_MSK;

		for (j = 0; j < rxcnt; j++) {
			u32 val;
			int p = 0;

			val = readl_relaxed(gi2c->se.base + SE_GENI_RX_FIFOn);
			while (gi2c->cur_rd < cur->len && p < sizeof(val)) {
				cur->buf[gi2c->cur_rd++] = val & 0xff;
				val >>= 8;
				p++;
			}
			if (gi2c->cur_rd == cur->len)
				break;
		}
	} else if (!(cur->flags & I2C_M_RD) &&
		   m_stat & M_TX_FIFO_WATERMARK_EN) {
		for (j = 0; j < gi2c->tx_wm; j++) {
			u32 temp;
			u32 val = 0;
			int p = 0;

			while (gi2c->cur_wr < cur->len && p < sizeof(val)) {
				temp = cur->buf[gi2c->cur_wr++];
				val |= temp << (p * 8);
				p++;
			}
			writel_relaxed(val, gi2c->se.base + SE_GENI_TX_FIFOn);
			/* TX Complete, Disable the TX Watermark interrupt */
			if (gi2c->cur_wr == cur->len) {
				writel_relaxed(0, gi2c->se.base +
						SE_GENI_TX_WATERMARK_REG);
				break;
			}
		}
	}
irqret:
	if (m_stat)
		writel_relaxed(m_stat, gi2c->se.base + SE_GENI_M_IRQ_CLEAR);

	if (dma) {
		if (dm_tx_st)
			writel_relaxed(dm_tx_st, gi2c->se.base +
						SE_DMA_TX_IRQ_CLR);
		if (dm_rx_st)
			writel_relaxed(dm_rx_st, gi2c->se.base +
						SE_DMA_RX_IRQ_CLR);
	}
	/* if this is err with done-bit not set, handle that through timeout. */
	if (m_stat & M_CMD_DONE_EN || m_stat & M_CMD_ABORT_EN)
		complete(&gi2c->done);
	else if (dm_tx_st & TX_DMA_DONE || dm_tx_st & TX_RESET_DONE)
		complete(&gi2c->done);
	else if (dm_rx_st & RX_DMA_DONE || dm_rx_st & RX_RESET_DONE)
		complete(&gi2c->done);

	spin_unlock_irqrestore(&gi2c->lock, flags);
	return IRQ_HANDLED;
}