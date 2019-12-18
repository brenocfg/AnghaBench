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
struct TYPE_2__ {char* name; int /*<<< orphan*/  direction; void* port; } ;
struct ep93xx_spi {void* zeropage; int /*<<< orphan*/ * dma_rx; void* dma_tx; TYPE_1__ dma_tx_data; TYPE_1__ dma_rx_data; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int ENODEV ; 
 int ENOMEM ; 
 void* EP93XX_DMA_SSP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 void* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ep93xx_spi_dma_filter ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xx_spi_setup_dma(struct ep93xx_spi *espi)
{
	dma_cap_mask_t mask;
	int ret;

	espi->zeropage = (void *)get_zeroed_page(GFP_KERNEL);
	if (!espi->zeropage)
		return -ENOMEM;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	espi->dma_rx_data.port = EP93XX_DMA_SSP;
	espi->dma_rx_data.direction = DMA_DEV_TO_MEM;
	espi->dma_rx_data.name = "ep93xx-spi-rx";

	espi->dma_rx = dma_request_channel(mask, ep93xx_spi_dma_filter,
					   &espi->dma_rx_data);
	if (!espi->dma_rx) {
		ret = -ENODEV;
		goto fail_free_page;
	}

	espi->dma_tx_data.port = EP93XX_DMA_SSP;
	espi->dma_tx_data.direction = DMA_MEM_TO_DEV;
	espi->dma_tx_data.name = "ep93xx-spi-tx";

	espi->dma_tx = dma_request_channel(mask, ep93xx_spi_dma_filter,
					   &espi->dma_tx_data);
	if (!espi->dma_tx) {
		ret = -ENODEV;
		goto fail_release_rx;
	}

	return 0;

fail_release_rx:
	dma_release_channel(espi->dma_rx);
	espi->dma_rx = NULL;
fail_free_page:
	free_page((unsigned long)espi->zeropage);

	return ret;
}