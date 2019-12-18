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
struct spi_message {int dummy; } ;
struct spi_controller {int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_tx; } ;
struct bcm2835_spi {int tx_dma_active; int rx_dma_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_controller*) ; 
 int /*<<< orphan*/  bcm2835_spi_undo_prologue (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static void bcm2835_spi_handle_err(struct spi_controller *ctlr,
				   struct spi_message *msg)
{
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);

	/* if an error occurred and we have an active dma, then terminate */
	dmaengine_terminate_sync(ctlr->dma_tx);
	bs->tx_dma_active = false;
	dmaengine_terminate_sync(ctlr->dma_rx);
	bs->rx_dma_active = false;
	bcm2835_spi_undo_prologue(bs);

	/* and reset */
	bcm2835_spi_reset_hw(ctlr);
}