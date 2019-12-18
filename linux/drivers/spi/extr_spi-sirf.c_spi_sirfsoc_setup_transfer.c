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
typedef  int u8 ;
typedef  int u32 ;
struct spi_transfer {int bits_per_word; int speed_hz; scalar_t__ len; int /*<<< orphan*/  rx_buf; scalar_t__ tx_buf; } ;
struct spi_device {int bits_per_word; int max_speed_hz; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct sirfsoc_spi {int ctrl_freq; int word_width; int fifo_size; scalar_t__ type; int tx_by_cmd; TYPE_1__* regs; scalar_t__ base; int /*<<< orphan*/  tx_word; int /*<<< orphan*/  rx_word; } ;
struct TYPE_2__ {scalar_t__ rx_dma_io_ctrl; scalar_t__ tx_dma_io_ctrl; scalar_t__ spi_ctrl; scalar_t__ usp_mode2; scalar_t__ usp_rx_frame_ctrl; scalar_t__ usp_tx_frame_ctrl; scalar_t__ rxfifo_ctrl; scalar_t__ txfifo_ctrl; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 scalar_t__ IS_DMA_VALID (struct spi_transfer*) ; 
 scalar_t__ SIRFSOC_MAX_CMD_BYTES ; 
 int SIRFSOC_SPI_CMD_BYTE_NUM (scalar_t__) ; 
 int SIRFSOC_SPI_CMD_MODE ; 
 int SIRFSOC_SPI_FIFO_THD_MASK (struct sirfsoc_spi*) ; 
 int SIRFSOC_SPI_FIFO_THD_OFFSET ; 
 int SIRFSOC_SPI_IO_MODE_SEL ; 
 int SIRFSOC_SPI_RX_DMA_FLUSH ; 
 int SIRFSOC_SPI_TRAN_DAT_FORMAT_12 ; 
 int SIRFSOC_SPI_TRAN_DAT_FORMAT_16 ; 
 int SIRFSOC_SPI_TRAN_DAT_FORMAT_32 ; 
 int SIRFSOC_SPI_TRAN_DAT_FORMAT_8 ; 
 int SIRFSOC_USP_CLK_10_11_MASK ; 
 int SIRFSOC_USP_CLK_10_11_OFFSET ; 
 int SIRFSOC_USP_CLK_12_15_MASK ; 
 int SIRFSOC_USP_CLK_12_15_OFFSET ; 
 int SIRFSOC_USP_CLK_DIVISOR_MASK ; 
 int SIRFSOC_USP_CLK_DIVISOR_OFFSET ; 
 int SIRFSOC_USP_RXD_DELAY_LEN ; 
 int SIRFSOC_USP_RXD_DELAY_OFFSET ; 
 int SIRFSOC_USP_RX_DATA_MASK ; 
 int SIRFSOC_USP_RX_DATA_OFFSET ; 
 int SIRFSOC_USP_RX_FRAME_MASK ; 
 int SIRFSOC_USP_RX_FRAME_OFFSET ; 
 int SIRFSOC_USP_RX_SHIFTER_MASK ; 
 int SIRFSOC_USP_RX_SHIFTER_OFFSET ; 
 int SIRFSOC_USP_TXD_DELAY_LEN ; 
 int SIRFSOC_USP_TXD_DELAY_OFFSET ; 
 int SIRFSOC_USP_TX_DATA_MASK ; 
 int SIRFSOC_USP_TX_DATA_OFFSET ; 
 int SIRFSOC_USP_TX_FRAME_MASK ; 
 int SIRFSOC_USP_TX_FRAME_OFFSET ; 
 int SIRFSOC_USP_TX_SHIFTER_MASK ; 
 int SIRFSOC_USP_TX_SHIFTER_OFFSET ; 
 int SIRFSOC_USP_TX_SYNC_MASK ; 
 int SIRFSOC_USP_TX_SYNC_OFFSET ; 
 scalar_t__ SIRF_REAL_SPI ; 
 scalar_t__ SIRF_USP_SPI_A7 ; 
 scalar_t__ SIRF_USP_SPI_P2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int readl (scalar_t__) ; 
 struct sirfsoc_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_sirfsoc_config_mode (struct spi_device*) ; 
 int /*<<< orphan*/  spi_sirfsoc_rx_word_u16 ; 
 int /*<<< orphan*/  spi_sirfsoc_rx_word_u32 ; 
 int /*<<< orphan*/  spi_sirfsoc_rx_word_u8 ; 
 int /*<<< orphan*/  spi_sirfsoc_tx_word_u16 ; 
 int /*<<< orphan*/  spi_sirfsoc_tx_word_u32 ; 
 int /*<<< orphan*/  spi_sirfsoc_tx_word_u8 ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int
spi_sirfsoc_setup_transfer(struct spi_device *spi, struct spi_transfer *t)
{
	struct sirfsoc_spi *sspi;
	u8 bits_per_word = 0;
	int hz = 0;
	u32 regval, txfifo_ctrl, rxfifo_ctrl, tx_frm_ctl, rx_frm_ctl, usp_mode2;

	sspi = spi_master_get_devdata(spi->master);

	bits_per_word = (t) ? t->bits_per_word : spi->bits_per_word;
	hz = t && t->speed_hz ? t->speed_hz : spi->max_speed_hz;

	usp_mode2 = regval = (sspi->ctrl_freq / (2 * hz)) - 1;
	if (regval > 0xFFFF || regval < 0) {
		dev_err(&spi->dev, "Speed %d not supported\n", hz);
		return -EINVAL;
	}
	switch (bits_per_word) {
	case 8:
		regval |= SIRFSOC_SPI_TRAN_DAT_FORMAT_8;
		sspi->rx_word = spi_sirfsoc_rx_word_u8;
		sspi->tx_word = spi_sirfsoc_tx_word_u8;
		break;
	case 12:
	case 16:
		regval |= (bits_per_word ==  12) ?
			SIRFSOC_SPI_TRAN_DAT_FORMAT_12 :
			SIRFSOC_SPI_TRAN_DAT_FORMAT_16;
		sspi->rx_word = spi_sirfsoc_rx_word_u16;
		sspi->tx_word = spi_sirfsoc_tx_word_u16;
		break;
	case 32:
		regval |= SIRFSOC_SPI_TRAN_DAT_FORMAT_32;
		sspi->rx_word = spi_sirfsoc_rx_word_u32;
		sspi->tx_word = spi_sirfsoc_tx_word_u32;
		break;
	default:
		dev_err(&spi->dev, "bpw %d not supported\n", bits_per_word);
		return -EINVAL;
	}
	sspi->word_width = DIV_ROUND_UP(bits_per_word, 8);
	txfifo_ctrl = (((sspi->fifo_size / 2) &
			SIRFSOC_SPI_FIFO_THD_MASK(sspi))
			<< SIRFSOC_SPI_FIFO_THD_OFFSET) |
			(sspi->word_width >> 1);
	rxfifo_ctrl = (((sspi->fifo_size / 2) &
			SIRFSOC_SPI_FIFO_THD_MASK(sspi))
			<< SIRFSOC_SPI_FIFO_THD_OFFSET) |
			(sspi->word_width >> 1);
	writel(txfifo_ctrl, sspi->base + sspi->regs->txfifo_ctrl);
	writel(rxfifo_ctrl, sspi->base + sspi->regs->rxfifo_ctrl);
	if (sspi->type == SIRF_USP_SPI_P2 ||
		sspi->type == SIRF_USP_SPI_A7) {
		tx_frm_ctl = 0;
		tx_frm_ctl |= ((bits_per_word - 1) & SIRFSOC_USP_TX_DATA_MASK)
				<< SIRFSOC_USP_TX_DATA_OFFSET;
		tx_frm_ctl |= ((bits_per_word + 1 + SIRFSOC_USP_TXD_DELAY_LEN
				- 1) & SIRFSOC_USP_TX_SYNC_MASK) <<
				SIRFSOC_USP_TX_SYNC_OFFSET;
		tx_frm_ctl |= ((bits_per_word + 1 + SIRFSOC_USP_TXD_DELAY_LEN
				+ 2 - 1) & SIRFSOC_USP_TX_FRAME_MASK) <<
				SIRFSOC_USP_TX_FRAME_OFFSET;
		tx_frm_ctl |= ((bits_per_word - 1) &
				SIRFSOC_USP_TX_SHIFTER_MASK) <<
				SIRFSOC_USP_TX_SHIFTER_OFFSET;
		rx_frm_ctl = 0;
		rx_frm_ctl |= ((bits_per_word - 1) & SIRFSOC_USP_RX_DATA_MASK)
				<< SIRFSOC_USP_RX_DATA_OFFSET;
		rx_frm_ctl |= ((bits_per_word + 1 + SIRFSOC_USP_RXD_DELAY_LEN
				+ 2 - 1) & SIRFSOC_USP_RX_FRAME_MASK) <<
				SIRFSOC_USP_RX_FRAME_OFFSET;
		rx_frm_ctl |= ((bits_per_word - 1)
				& SIRFSOC_USP_RX_SHIFTER_MASK) <<
				SIRFSOC_USP_RX_SHIFTER_OFFSET;
		writel(tx_frm_ctl | (((usp_mode2 >> 10) &
			SIRFSOC_USP_CLK_10_11_MASK) <<
			SIRFSOC_USP_CLK_10_11_OFFSET),
			sspi->base + sspi->regs->usp_tx_frame_ctrl);
		writel(rx_frm_ctl | (((usp_mode2 >> 12) &
			SIRFSOC_USP_CLK_12_15_MASK) <<
			SIRFSOC_USP_CLK_12_15_OFFSET),
			sspi->base + sspi->regs->usp_rx_frame_ctrl);
		writel(readl(sspi->base + sspi->regs->usp_mode2) |
			((usp_mode2 & SIRFSOC_USP_CLK_DIVISOR_MASK) <<
			SIRFSOC_USP_CLK_DIVISOR_OFFSET) |
			(SIRFSOC_USP_RXD_DELAY_LEN <<
			 SIRFSOC_USP_RXD_DELAY_OFFSET) |
			(SIRFSOC_USP_TXD_DELAY_LEN <<
			 SIRFSOC_USP_TXD_DELAY_OFFSET),
			sspi->base + sspi->regs->usp_mode2);
	}
	if (sspi->type == SIRF_REAL_SPI)
		writel(regval, sspi->base + sspi->regs->spi_ctrl);
	spi_sirfsoc_config_mode(spi);
	if (sspi->type == SIRF_REAL_SPI) {
		if (t && t->tx_buf && !t->rx_buf &&
			(t->len <= SIRFSOC_MAX_CMD_BYTES)) {
			sspi->tx_by_cmd = true;
			writel(readl(sspi->base + sspi->regs->spi_ctrl) |
				(SIRFSOC_SPI_CMD_BYTE_NUM((t->len - 1)) |
				SIRFSOC_SPI_CMD_MODE),
				sspi->base + sspi->regs->spi_ctrl);
		} else {
			sspi->tx_by_cmd = false;
			writel(readl(sspi->base + sspi->regs->spi_ctrl) &
				~SIRFSOC_SPI_CMD_MODE,
				sspi->base + sspi->regs->spi_ctrl);
		}
	}
	if (IS_DMA_VALID(t)) {
		/* Enable DMA mode for RX, TX */
		writel(0, sspi->base + sspi->regs->tx_dma_io_ctrl);
		writel(SIRFSOC_SPI_RX_DMA_FLUSH,
			sspi->base + sspi->regs->rx_dma_io_ctrl);
	} else {
		/* Enable IO mode for RX, TX */
		writel(SIRFSOC_SPI_IO_MODE_SEL,
			sspi->base + sspi->regs->tx_dma_io_ctrl);
		writel(SIRFSOC_SPI_IO_MODE_SEL,
			sspi->base + sspi->regs->rx_dma_io_ctrl);
	}
	return 0;
}