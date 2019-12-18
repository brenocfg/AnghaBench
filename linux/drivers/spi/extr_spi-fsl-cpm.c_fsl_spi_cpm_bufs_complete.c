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
struct spi_transfer {int /*<<< orphan*/  len; } ;
struct mpc8xxx_spi {struct spi_transfer* xfer_in_progress; int /*<<< orphan*/  rx_dma; scalar_t__ map_rx_dma; int /*<<< orphan*/  tx_dma; scalar_t__ map_tx_dma; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fsl_spi_cpm_bufs_complete(struct mpc8xxx_spi *mspi)
{
	struct device *dev = mspi->dev;
	struct spi_transfer *t = mspi->xfer_in_progress;

	if (mspi->map_tx_dma)
		dma_unmap_single(dev, mspi->tx_dma, t->len, DMA_TO_DEVICE);
	if (mspi->map_rx_dma)
		dma_unmap_single(dev, mspi->rx_dma, t->len, DMA_FROM_DEVICE);
	mspi->xfer_in_progress = NULL;
}