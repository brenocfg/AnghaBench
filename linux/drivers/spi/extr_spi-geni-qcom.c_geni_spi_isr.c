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
struct spi_master {int dummy; } ;
struct geni_se {scalar_t__ base; } ;
struct spi_geni_master {scalar_t__ cur_mcmd; int /*<<< orphan*/  lock; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  cur_bits_per_word; scalar_t__ rx_rem_bytes; int /*<<< orphan*/  dev; scalar_t__ tx_rem_bytes; struct geni_se se; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CMD_CS ; 
 scalar_t__ CMD_NONE ; 
 scalar_t__ CMD_XFER ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int M_CMD_ABORT_EN ; 
 int M_CMD_CANCEL_EN ; 
 int M_CMD_DONE_EN ; 
 int M_RX_FIFO_LAST_EN ; 
 int M_RX_FIFO_WATERMARK_EN ; 
 int M_TX_FIFO_WATERMARK_EN ; 
 scalar_t__ SE_GENI_M_IRQ_CLEAR ; 
 scalar_t__ SE_GENI_M_IRQ_STATUS ; 
 scalar_t__ SE_GENI_TX_WATERMARK_REG ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geni_spi_handle_rx (struct spi_geni_master*) ; 
 int /*<<< orphan*/  geni_spi_handle_tx (struct spi_geni_master*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct spi_geni_master* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t geni_spi_isr(int irq, void *data)
{
	struct spi_master *spi = data;
	struct spi_geni_master *mas = spi_master_get_devdata(spi);
	struct geni_se *se = &mas->se;
	u32 m_irq;
	unsigned long flags;

	if (mas->cur_mcmd == CMD_NONE)
		return IRQ_NONE;

	spin_lock_irqsave(&mas->lock, flags);
	m_irq = readl(se->base + SE_GENI_M_IRQ_STATUS);

	if ((m_irq & M_RX_FIFO_WATERMARK_EN) || (m_irq & M_RX_FIFO_LAST_EN))
		geni_spi_handle_rx(mas);

	if (m_irq & M_TX_FIFO_WATERMARK_EN)
		geni_spi_handle_tx(mas);

	if (m_irq & M_CMD_DONE_EN) {
		if (mas->cur_mcmd == CMD_XFER)
			spi_finalize_current_transfer(spi);
		else if (mas->cur_mcmd == CMD_CS)
			complete(&mas->xfer_done);
		mas->cur_mcmd = CMD_NONE;
		/*
		 * If this happens, then a CMD_DONE came before all the Tx
		 * buffer bytes were sent out. This is unusual, log this
		 * condition and disable the WM interrupt to prevent the
		 * system from stalling due an interrupt storm.
		 * If this happens when all Rx bytes haven't been received, log
		 * the condition.
		 * The only known time this can happen is if bits_per_word != 8
		 * and some registers that expect xfer lengths in num spi_words
		 * weren't written correctly.
		 */
		if (mas->tx_rem_bytes) {
			writel(0, se->base + SE_GENI_TX_WATERMARK_REG);
			dev_err(mas->dev, "Premature done. tx_rem = %d bpw%d\n",
				mas->tx_rem_bytes, mas->cur_bits_per_word);
		}
		if (mas->rx_rem_bytes)
			dev_err(mas->dev, "Premature done. rx_rem = %d bpw%d\n",
				mas->rx_rem_bytes, mas->cur_bits_per_word);
	}

	if ((m_irq & M_CMD_CANCEL_EN) || (m_irq & M_CMD_ABORT_EN)) {
		mas->cur_mcmd = CMD_NONE;
		complete(&mas->xfer_done);
	}

	writel(m_irq, se->base + SE_GENI_M_IRQ_CLEAR);
	spin_unlock_irqrestore(&mas->lock, flags);
	return IRQ_HANDLED;
}