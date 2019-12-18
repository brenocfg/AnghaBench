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
struct spi_transfer {int bits_per_word; int len; int speed_hz; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_device {int mode; } ;
struct rockchip_spi {int rsd; int fifo_len; scalar_t__ regs; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int CR0_BHT_8BIT ; 
 int CR0_BHT_OFFSET ; 
 int CR0_DFS_16BIT ; 
 int CR0_DFS_4BIT ; 
 int CR0_DFS_8BIT ; 
 int CR0_DFS_OFFSET ; 
 int CR0_EM_BIG ; 
 int CR0_EM_OFFSET ; 
 int CR0_FBM_LSB ; 
 int CR0_FBM_OFFSET ; 
 int CR0_FRF_OFFSET ; 
 int CR0_FRF_SPI ; 
 int CR0_RSD_OFFSET ; 
 int CR0_SCPH_OFFSET ; 
 int CR0_SSD_OFFSET ; 
 int CR0_SSD_ONE ; 
 int CR0_XFM_OFFSET ; 
 int CR0_XFM_RO ; 
 int CR0_XFM_TO ; 
 int CR0_XFM_TR ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int RF_DMA_EN ; 
 scalar_t__ ROCKCHIP_SPI_BAUDR ; 
 scalar_t__ ROCKCHIP_SPI_CTRLR0 ; 
 scalar_t__ ROCKCHIP_SPI_CTRLR1 ; 
 scalar_t__ ROCKCHIP_SPI_DMACR ; 
 scalar_t__ ROCKCHIP_SPI_DMARDLR ; 
 scalar_t__ ROCKCHIP_SPI_DMATDLR ; 
 scalar_t__ ROCKCHIP_SPI_RXFTLR ; 
 int SPI_LSB_FIRST ; 
 int TF_DMA_EN ; 
 int /*<<< orphan*/  unreachable () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void rockchip_spi_config(struct rockchip_spi *rs,
		struct spi_device *spi, struct spi_transfer *xfer,
		bool use_dma)
{
	u32 cr0 = CR0_FRF_SPI  << CR0_FRF_OFFSET
	        | CR0_BHT_8BIT << CR0_BHT_OFFSET
	        | CR0_SSD_ONE  << CR0_SSD_OFFSET
	        | CR0_EM_BIG   << CR0_EM_OFFSET;
	u32 cr1;
	u32 dmacr = 0;

	cr0 |= rs->rsd << CR0_RSD_OFFSET;
	cr0 |= (spi->mode & 0x3U) << CR0_SCPH_OFFSET;
	if (spi->mode & SPI_LSB_FIRST)
		cr0 |= CR0_FBM_LSB << CR0_FBM_OFFSET;

	if (xfer->rx_buf && xfer->tx_buf)
		cr0 |= CR0_XFM_TR << CR0_XFM_OFFSET;
	else if (xfer->rx_buf)
		cr0 |= CR0_XFM_RO << CR0_XFM_OFFSET;
	else if (use_dma)
		cr0 |= CR0_XFM_TO << CR0_XFM_OFFSET;

	switch (xfer->bits_per_word) {
	case 4:
		cr0 |= CR0_DFS_4BIT << CR0_DFS_OFFSET;
		cr1 = xfer->len - 1;
		break;
	case 8:
		cr0 |= CR0_DFS_8BIT << CR0_DFS_OFFSET;
		cr1 = xfer->len - 1;
		break;
	case 16:
		cr0 |= CR0_DFS_16BIT << CR0_DFS_OFFSET;
		cr1 = xfer->len / 2 - 1;
		break;
	default:
		/* we only whitelist 4, 8 and 16 bit words in
		 * master->bits_per_word_mask, so this shouldn't
		 * happen
		 */
		unreachable();
	}

	if (use_dma) {
		if (xfer->tx_buf)
			dmacr |= TF_DMA_EN;
		if (xfer->rx_buf)
			dmacr |= RF_DMA_EN;
	}

	writel_relaxed(cr0, rs->regs + ROCKCHIP_SPI_CTRLR0);
	writel_relaxed(cr1, rs->regs + ROCKCHIP_SPI_CTRLR1);

	/* unfortunately setting the fifo threshold level to generate an
	 * interrupt exactly when the fifo is full doesn't seem to work,
	 * so we need the strict inequality here
	 */
	if (xfer->len < rs->fifo_len)
		writel_relaxed(xfer->len - 1, rs->regs + ROCKCHIP_SPI_RXFTLR);
	else
		writel_relaxed(rs->fifo_len / 2 - 1, rs->regs + ROCKCHIP_SPI_RXFTLR);

	writel_relaxed(rs->fifo_len / 2, rs->regs + ROCKCHIP_SPI_DMATDLR);
	writel_relaxed(0, rs->regs + ROCKCHIP_SPI_DMARDLR);
	writel_relaxed(dmacr, rs->regs + ROCKCHIP_SPI_DMACR);

	/* the hardware only supports an even clock divisor, so
	 * round divisor = spiclk / speed up to nearest even number
	 * so that the resulting speed is <= the requested speed
	 */
	writel_relaxed(2 * DIV_ROUND_UP(rs->freq, 2 * xfer->speed_hz),
			rs->regs + ROCKCHIP_SPI_BAUDR);
}