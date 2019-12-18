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
struct spi_master {int dummy; } ;
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct ep93xx_spi {struct sg_table tx_sgt; struct dma_chan* dma_tx; struct sg_table rx_sgt; struct dma_chan* dma_rx; } ;
struct dma_chan {TYPE_1__* device; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ep93xx_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void ep93xx_spi_dma_finish(struct spi_master *master,
				  enum dma_data_direction dir)
{
	struct ep93xx_spi *espi = spi_master_get_devdata(master);
	struct dma_chan *chan;
	struct sg_table *sgt;

	if (dir == DMA_FROM_DEVICE) {
		chan = espi->dma_rx;
		sgt = &espi->rx_sgt;
	} else {
		chan = espi->dma_tx;
		sgt = &espi->tx_sgt;
	}

	dma_unmap_sg(chan->device->dev, sgt->sgl, sgt->nents, dir);
}