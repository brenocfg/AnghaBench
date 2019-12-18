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
struct TYPE_2__ {void** dma_chan; } ;
struct sprd_spi {TYPE_1__ dma; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int PTR_ERR (void*) ; 
 size_t SPRD_SPI_RX ; 
 size_t SPRD_SPI_TX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 
 void* dma_request_chan (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sprd_spi_dma_request(struct sprd_spi *ss)
{
	ss->dma.dma_chan[SPRD_SPI_RX] = dma_request_chan(ss->dev, "rx_chn");
	if (IS_ERR_OR_NULL(ss->dma.dma_chan[SPRD_SPI_RX])) {
		if (PTR_ERR(ss->dma.dma_chan[SPRD_SPI_RX]) == -EPROBE_DEFER)
			return PTR_ERR(ss->dma.dma_chan[SPRD_SPI_RX]);

		dev_err(ss->dev, "request RX DMA channel failed!\n");
		return PTR_ERR(ss->dma.dma_chan[SPRD_SPI_RX]);
	}

	ss->dma.dma_chan[SPRD_SPI_TX]  = dma_request_chan(ss->dev, "tx_chn");
	if (IS_ERR_OR_NULL(ss->dma.dma_chan[SPRD_SPI_TX])) {
		if (PTR_ERR(ss->dma.dma_chan[SPRD_SPI_TX]) == -EPROBE_DEFER)
			return PTR_ERR(ss->dma.dma_chan[SPRD_SPI_TX]);

		dev_err(ss->dev, "request TX DMA channel failed!\n");
		dma_release_channel(ss->dma.dma_chan[SPRD_SPI_RX]);
		return PTR_ERR(ss->dma.dma_chan[SPRD_SPI_TX]);
	}

	return 0;
}