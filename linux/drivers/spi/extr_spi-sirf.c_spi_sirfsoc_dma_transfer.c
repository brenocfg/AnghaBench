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
struct spi_transfer {int len; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct sirfsoc_spi {int type; scalar_t__ left_tx_word; scalar_t__ dat_max_frm_len; unsigned long word_width; void* rx; TYPE_1__* regs; scalar_t__ base; void* dst_start; void* src_start; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  tx_done; scalar_t__ left_rx_word; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  rx_done; scalar_t__ tx; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/ * callback_param; void* callback; } ;
struct TYPE_2__ {scalar_t__ tx_rx_en; scalar_t__ txfifo_op; scalar_t__ rxfifo_op; scalar_t__ rx_dma_io_len; scalar_t__ tx_dma_io_len; scalar_t__ spi_ctrl; scalar_t__ int_st; scalar_t__ usp_int_en_clr; scalar_t__ int_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned long SIRFSOC_SPI_ENA_AUTO_CLR ; 
 unsigned long SIRFSOC_SPI_FIFO_RESET ; 
 unsigned long SIRFSOC_SPI_FIFO_START ; 
 unsigned long SIRFSOC_SPI_MUL_DAT_MODE ; 
 unsigned long SIRFSOC_SPI_RX_EN ; 
 unsigned long SIRFSOC_SPI_TX_EN ; 
#define  SIRF_REAL_SPI 130 
#define  SIRF_USP_SPI_A7 129 
#define  SIRF_USP_SPI_P2 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 void* dma_map_single (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 unsigned long readl (scalar_t__) ; 
 struct sirfsoc_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 void* spi_sirfsoc_dma_fini_callback ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void spi_sirfsoc_dma_transfer(struct spi_device *spi,
	struct spi_transfer *t)
{
	struct sirfsoc_spi *sspi;
	struct dma_async_tx_descriptor *rx_desc, *tx_desc;
	int timeout = t->len * 10;

	sspi = spi_master_get_devdata(spi->master);
	writel(SIRFSOC_SPI_FIFO_RESET, sspi->base + sspi->regs->rxfifo_op);
	writel(SIRFSOC_SPI_FIFO_RESET, sspi->base + sspi->regs->txfifo_op);
	switch (sspi->type) {
	case SIRF_REAL_SPI:
		writel(SIRFSOC_SPI_FIFO_START,
			sspi->base + sspi->regs->rxfifo_op);
		writel(SIRFSOC_SPI_FIFO_START,
			sspi->base + sspi->regs->txfifo_op);
		writel(0, sspi->base + sspi->regs->int_en);
		break;
	case SIRF_USP_SPI_P2:
		writel(0x0, sspi->base + sspi->regs->rxfifo_op);
		writel(0x0, sspi->base + sspi->regs->txfifo_op);
		writel(0, sspi->base + sspi->regs->int_en);
		break;
	case SIRF_USP_SPI_A7:
		writel(0x0, sspi->base + sspi->regs->rxfifo_op);
		writel(0x0, sspi->base + sspi->regs->txfifo_op);
		writel(~0UL, sspi->base + sspi->regs->usp_int_en_clr);
		break;
	}
	writel(readl(sspi->base + sspi->regs->int_st),
		sspi->base + sspi->regs->int_st);
	if (sspi->left_tx_word < sspi->dat_max_frm_len) {
		switch (sspi->type) {
		case SIRF_REAL_SPI:
			writel(readl(sspi->base + sspi->regs->spi_ctrl) |
				SIRFSOC_SPI_ENA_AUTO_CLR |
				SIRFSOC_SPI_MUL_DAT_MODE,
				sspi->base + sspi->regs->spi_ctrl);
			writel(sspi->left_tx_word - 1,
				sspi->base + sspi->regs->tx_dma_io_len);
			writel(sspi->left_tx_word - 1,
				sspi->base + sspi->regs->rx_dma_io_len);
			break;
		case SIRF_USP_SPI_P2:
		case SIRF_USP_SPI_A7:
			/*USP simulate SPI, tx/rx_dma_io_len indicates bytes*/
			writel(sspi->left_tx_word * sspi->word_width,
				sspi->base + sspi->regs->tx_dma_io_len);
			writel(sspi->left_tx_word * sspi->word_width,
				sspi->base + sspi->regs->rx_dma_io_len);
			break;
		}
	} else {
		if (sspi->type == SIRF_REAL_SPI)
			writel(readl(sspi->base + sspi->regs->spi_ctrl),
				sspi->base + sspi->regs->spi_ctrl);
		writel(0, sspi->base + sspi->regs->tx_dma_io_len);
		writel(0, sspi->base + sspi->regs->rx_dma_io_len);
	}
	sspi->dst_start = dma_map_single(&spi->dev, sspi->rx, t->len,
					(t->tx_buf != t->rx_buf) ?
					DMA_FROM_DEVICE : DMA_BIDIRECTIONAL);
	rx_desc = dmaengine_prep_slave_single(sspi->rx_chan,
		sspi->dst_start, t->len, DMA_DEV_TO_MEM,
		DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	rx_desc->callback = spi_sirfsoc_dma_fini_callback;
	rx_desc->callback_param = &sspi->rx_done;

	sspi->src_start = dma_map_single(&spi->dev, (void *)sspi->tx, t->len,
					(t->tx_buf != t->rx_buf) ?
					DMA_TO_DEVICE : DMA_BIDIRECTIONAL);
	tx_desc = dmaengine_prep_slave_single(sspi->tx_chan,
		sspi->src_start, t->len, DMA_MEM_TO_DEV,
		DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	tx_desc->callback = spi_sirfsoc_dma_fini_callback;
	tx_desc->callback_param = &sspi->tx_done;

	dmaengine_submit(tx_desc);
	dmaengine_submit(rx_desc);
	dma_async_issue_pending(sspi->tx_chan);
	dma_async_issue_pending(sspi->rx_chan);
	writel(SIRFSOC_SPI_RX_EN | SIRFSOC_SPI_TX_EN,
			sspi->base + sspi->regs->tx_rx_en);
	if (sspi->type == SIRF_USP_SPI_P2 ||
		sspi->type == SIRF_USP_SPI_A7) {
		writel(SIRFSOC_SPI_FIFO_START,
			sspi->base + sspi->regs->rxfifo_op);
		writel(SIRFSOC_SPI_FIFO_START,
			sspi->base + sspi->regs->txfifo_op);
	}
	if (wait_for_completion_timeout(&sspi->rx_done, timeout) == 0) {
		dev_err(&spi->dev, "transfer timeout\n");
		dmaengine_terminate_all(sspi->rx_chan);
	} else
		sspi->left_rx_word = 0;
	/*
	 * we only wait tx-done event if transferring by DMA. for PIO,
	 * we get rx data by writing tx data, so if rx is done, tx has
	 * done earlier
	 */
	if (wait_for_completion_timeout(&sspi->tx_done, timeout) == 0) {
		dev_err(&spi->dev, "transfer timeout\n");
		if (sspi->type == SIRF_USP_SPI_P2 ||
			sspi->type == SIRF_USP_SPI_A7)
			writel(0, sspi->base + sspi->regs->tx_rx_en);
		dmaengine_terminate_all(sspi->tx_chan);
	}
	dma_unmap_single(&spi->dev, sspi->src_start, t->len, DMA_TO_DEVICE);
	dma_unmap_single(&spi->dev, sspi->dst_start, t->len, DMA_FROM_DEVICE);
	/* TX, RX FIFO stop */
	writel(0, sspi->base + sspi->regs->rxfifo_op);
	writel(0, sspi->base + sspi->regs->txfifo_op);
	if (sspi->left_tx_word >= sspi->dat_max_frm_len)
		writel(0, sspi->base + sspi->regs->tx_rx_en);
	if (sspi->type == SIRF_USP_SPI_P2 ||
		sspi->type == SIRF_USP_SPI_A7)
		writel(0, sspi->base + sspi->regs->tx_rx_en);
}