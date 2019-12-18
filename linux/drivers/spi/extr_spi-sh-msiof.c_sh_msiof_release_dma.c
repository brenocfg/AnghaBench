#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_controller {TYPE_2__* dma_tx; TYPE_2__* dma_rx; } ;
struct sh_msiof_spi_priv {scalar_t__ tx_dma_page; scalar_t__ rx_dma_page; int /*<<< orphan*/  tx_dma_addr; int /*<<< orphan*/  rx_dma_addr; struct spi_controller* ctlr; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void sh_msiof_release_dma(struct sh_msiof_spi_priv *p)
{
	struct spi_controller *ctlr = p->ctlr;

	if (!ctlr->dma_tx)
		return;

	dma_unmap_single(ctlr->dma_rx->device->dev, p->rx_dma_addr, PAGE_SIZE,
			 DMA_FROM_DEVICE);
	dma_unmap_single(ctlr->dma_tx->device->dev, p->tx_dma_addr, PAGE_SIZE,
			 DMA_TO_DEVICE);
	free_page((unsigned long)p->rx_dma_page);
	free_page((unsigned long)p->tx_dma_page);
	dma_release_channel(ctlr->dma_rx);
	dma_release_channel(ctlr->dma_tx);
}