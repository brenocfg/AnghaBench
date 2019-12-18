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
struct spi_transfer {int len; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct sirfsoc_spi {scalar_t__ left_tx_word; scalar_t__ left_rx_word; int type; int word_width; unsigned int fifo_size; TYPE_1__* regs; scalar_t__ base; int /*<<< orphan*/  (* rx_word ) (struct sirfsoc_spi*) ;int /*<<< orphan*/  rx_done; int /*<<< orphan*/  tx_done; int /*<<< orphan*/  (* tx_word ) (struct sirfsoc_spi*) ;} ;
struct TYPE_2__ {scalar_t__ txfifo_op; scalar_t__ rxfifo_op; scalar_t__ tx_rx_en; scalar_t__ rxfifo_st; scalar_t__ int_en; scalar_t__ txfifo_st; scalar_t__ rx_dma_io_len; scalar_t__ tx_dma_io_len; scalar_t__ spi_ctrl; scalar_t__ int_st; scalar_t__ usp_int_en_clr; } ;

/* Variables and functions */
 unsigned long SIRFSOC_SPI_ENA_AUTO_CLR ; 
 unsigned long SIRFSOC_SPI_FIFO_EMPTY_MASK (struct sirfsoc_spi*) ; 
 unsigned long SIRFSOC_SPI_FIFO_FULL_MASK (struct sirfsoc_spi*) ; 
 unsigned long SIRFSOC_SPI_FIFO_RESET ; 
 unsigned long SIRFSOC_SPI_FIFO_START ; 
 unsigned long SIRFSOC_SPI_MUL_DAT_MODE ; 
 unsigned long SIRFSOC_SPI_RX_EN ; 
 unsigned long SIRFSOC_SPI_RX_IO_DMA_INT_EN ; 
 unsigned long SIRFSOC_SPI_RX_OFLOW_INT_EN ; 
 unsigned long SIRFSOC_SPI_TXFIFO_EMPTY_INT_EN ; 
 unsigned long SIRFSOC_SPI_TX_EN ; 
 unsigned long SIRFSOC_SPI_TX_UFLOW_INT_EN ; 
#define  SIRF_REAL_SPI 130 
#define  SIRF_USP_SPI_A7 129 
#define  SIRF_USP_SPI_P2 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long min (int,unsigned int) ; 
 unsigned long readl (scalar_t__) ; 
 struct sirfsoc_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sirfsoc_spi*) ; 
 int /*<<< orphan*/  stub2 (struct sirfsoc_spi*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void spi_sirfsoc_pio_transfer(struct spi_device *spi,
		struct spi_transfer *t)
{
	struct sirfsoc_spi *sspi;
	int timeout = t->len * 10;
	unsigned int data_units;

	sspi = spi_master_get_devdata(spi->master);
	do {
		writel(SIRFSOC_SPI_FIFO_RESET,
			sspi->base + sspi->regs->rxfifo_op);
		writel(SIRFSOC_SPI_FIFO_RESET,
			sspi->base + sspi->regs->txfifo_op);
		switch (sspi->type) {
		case SIRF_USP_SPI_P2:
			writel(0x0, sspi->base + sspi->regs->rxfifo_op);
			writel(0x0, sspi->base + sspi->regs->txfifo_op);
			writel(0, sspi->base + sspi->regs->int_en);
			writel(readl(sspi->base + sspi->regs->int_st),
				sspi->base + sspi->regs->int_st);
			writel(min((sspi->left_tx_word * sspi->word_width),
				sspi->fifo_size),
				sspi->base + sspi->regs->tx_dma_io_len);
			writel(min((sspi->left_rx_word * sspi->word_width),
				sspi->fifo_size),
				sspi->base + sspi->regs->rx_dma_io_len);
			break;
		case SIRF_USP_SPI_A7:
			writel(0x0, sspi->base + sspi->regs->rxfifo_op);
			writel(0x0, sspi->base + sspi->regs->txfifo_op);
			writel(~0UL, sspi->base + sspi->regs->usp_int_en_clr);
			writel(readl(sspi->base + sspi->regs->int_st),
				sspi->base + sspi->regs->int_st);
			writel(min((sspi->left_tx_word * sspi->word_width),
				sspi->fifo_size),
				sspi->base + sspi->regs->tx_dma_io_len);
			writel(min((sspi->left_rx_word * sspi->word_width),
				sspi->fifo_size),
				sspi->base + sspi->regs->rx_dma_io_len);
			break;
		case SIRF_REAL_SPI:
			writel(SIRFSOC_SPI_FIFO_START,
				sspi->base + sspi->regs->rxfifo_op);
			writel(SIRFSOC_SPI_FIFO_START,
				sspi->base + sspi->regs->txfifo_op);
			writel(0, sspi->base + sspi->regs->int_en);
			writel(readl(sspi->base + sspi->regs->int_st),
				sspi->base + sspi->regs->int_st);
			writel(readl(sspi->base + sspi->regs->spi_ctrl) |
				SIRFSOC_SPI_MUL_DAT_MODE |
				SIRFSOC_SPI_ENA_AUTO_CLR,
				sspi->base + sspi->regs->spi_ctrl);
			data_units = sspi->fifo_size / sspi->word_width;
			writel(min(sspi->left_tx_word, data_units) - 1,
				sspi->base + sspi->regs->tx_dma_io_len);
			writel(min(sspi->left_rx_word, data_units) - 1,
				sspi->base + sspi->regs->rx_dma_io_len);
			break;
		}
		while (!((readl(sspi->base + sspi->regs->txfifo_st)
			& SIRFSOC_SPI_FIFO_FULL_MASK(sspi))) &&
			sspi->left_tx_word)
			sspi->tx_word(sspi);
		writel(SIRFSOC_SPI_TXFIFO_EMPTY_INT_EN |
			SIRFSOC_SPI_TX_UFLOW_INT_EN |
			SIRFSOC_SPI_RX_OFLOW_INT_EN |
			SIRFSOC_SPI_RX_IO_DMA_INT_EN,
			sspi->base + sspi->regs->int_en);
		writel(SIRFSOC_SPI_RX_EN | SIRFSOC_SPI_TX_EN,
			sspi->base + sspi->regs->tx_rx_en);
		if (sspi->type == SIRF_USP_SPI_P2 ||
			sspi->type == SIRF_USP_SPI_A7) {
			writel(SIRFSOC_SPI_FIFO_START,
				sspi->base + sspi->regs->rxfifo_op);
			writel(SIRFSOC_SPI_FIFO_START,
				sspi->base + sspi->regs->txfifo_op);
		}
		if (!wait_for_completion_timeout(&sspi->tx_done, timeout) ||
			!wait_for_completion_timeout(&sspi->rx_done, timeout)) {
			dev_err(&spi->dev, "transfer timeout\n");
			if (sspi->type == SIRF_USP_SPI_P2 ||
				sspi->type == SIRF_USP_SPI_A7)
				writel(0, sspi->base + sspi->regs->tx_rx_en);
			break;
		}
		while (!((readl(sspi->base + sspi->regs->rxfifo_st)
			& SIRFSOC_SPI_FIFO_EMPTY_MASK(sspi))) &&
			sspi->left_rx_word)
			sspi->rx_word(sspi);
		if (sspi->type == SIRF_USP_SPI_P2 ||
			sspi->type == SIRF_USP_SPI_A7)
			writel(0, sspi->base + sspi->regs->tx_rx_en);
		writel(0, sspi->base + sspi->regs->rxfifo_op);
		writel(0, sspi->base + sspi->regs->txfifo_op);
	} while (sspi->left_tx_word != 0 || sspi->left_rx_word != 0);
}