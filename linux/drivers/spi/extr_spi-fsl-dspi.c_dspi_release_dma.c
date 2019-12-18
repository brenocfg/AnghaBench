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
struct fsl_dspi_dma {scalar_t__ chan_rx; int /*<<< orphan*/  rx_dma_phys; scalar_t__ chan_tx; int /*<<< orphan*/  tx_dma_phys; } ;
struct fsl_dspi {TYPE_1__* pdev; struct fsl_dspi_dma* dma; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DSPI_DMA_BUFSIZE ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dspi_release_dma(struct fsl_dspi *dspi)
{
	struct fsl_dspi_dma *dma = dspi->dma;
	struct device *dev = &dspi->pdev->dev;

	if (!dma)
		return;

	if (dma->chan_tx) {
		dma_unmap_single(dev, dma->tx_dma_phys,
				 DSPI_DMA_BUFSIZE, DMA_TO_DEVICE);
		dma_release_channel(dma->chan_tx);
	}

	if (dma->chan_rx) {
		dma_unmap_single(dev, dma->rx_dma_phys,
				 DSPI_DMA_BUFSIZE, DMA_FROM_DEVICE);
		dma_release_channel(dma->chan_rx);
	}
}