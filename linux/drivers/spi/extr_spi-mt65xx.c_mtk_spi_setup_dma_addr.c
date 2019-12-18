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
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {int tx_dma; int rx_dma; } ;
struct spi_master {int dummy; } ;
struct mtk_spi {scalar_t__ base; TYPE_1__* dev_comp; scalar_t__ rx_sgl; scalar_t__ tx_sgl; } ;
struct TYPE_2__ {scalar_t__ dma_ext; } ;

/* Variables and functions */
 int MTK_SPI_32BITS_MASK ; 
 scalar_t__ SPI_RX_DST_REG ; 
 scalar_t__ SPI_RX_DST_REG_64 ; 
 scalar_t__ SPI_TX_SRC_REG ; 
 scalar_t__ SPI_TX_SRC_REG_64 ; 
 struct mtk_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_spi_setup_dma_addr(struct spi_master *master,
				   struct spi_transfer *xfer)
{
	struct mtk_spi *mdata = spi_master_get_devdata(master);

	if (mdata->tx_sgl) {
		writel((u32)(xfer->tx_dma & MTK_SPI_32BITS_MASK),
		       mdata->base + SPI_TX_SRC_REG);
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
		if (mdata->dev_comp->dma_ext)
			writel((u32)(xfer->tx_dma >> 32),
			       mdata->base + SPI_TX_SRC_REG_64);
#endif
	}

	if (mdata->rx_sgl) {
		writel((u32)(xfer->rx_dma & MTK_SPI_32BITS_MASK),
		       mdata->base + SPI_RX_DST_REG);
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
		if (mdata->dev_comp->dma_ext)
			writel((u32)(xfer->rx_dma >> 32),
			       mdata->base + SPI_RX_DST_REG_64);
#endif
	}
}