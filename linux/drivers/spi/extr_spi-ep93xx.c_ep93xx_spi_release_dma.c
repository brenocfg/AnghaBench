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
struct ep93xx_spi {scalar_t__ zeropage; int /*<<< orphan*/  tx_sgt; scalar_t__ dma_tx; int /*<<< orphan*/  rx_sgt; scalar_t__ dma_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ep93xx_spi_release_dma(struct ep93xx_spi *espi)
{
	if (espi->dma_rx) {
		dma_release_channel(espi->dma_rx);
		sg_free_table(&espi->rx_sgt);
	}
	if (espi->dma_tx) {
		dma_release_channel(espi->dma_tx);
		sg_free_table(&espi->tx_sgt);
	}

	if (espi->zeropage)
		free_page((unsigned long)espi->zeropage);
}