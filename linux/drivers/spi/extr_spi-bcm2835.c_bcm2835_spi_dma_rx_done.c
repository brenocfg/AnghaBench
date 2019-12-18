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
struct spi_controller {int /*<<< orphan*/  xfer_completion; int /*<<< orphan*/  dma_tx; } ;
struct bcm2835_spi {int tx_dma_active; int rx_dma_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_controller*) ; 
 int /*<<< orphan*/  bcm2835_spi_undo_prologue (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_terminate_async (int /*<<< orphan*/ ) ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static void bcm2835_spi_dma_rx_done(void *data)
{
	struct spi_controller *ctlr = data;
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);

	/* terminate tx-dma as we do not have an irq for it
	 * because when the rx dma will terminate and this callback
	 * is called the tx-dma must have finished - can't get to this
	 * situation otherwise...
	 */
	dmaengine_terminate_async(ctlr->dma_tx);
	bs->tx_dma_active = false;
	bs->rx_dma_active = false;
	bcm2835_spi_undo_prologue(bs);

	/* reset fifo and HW */
	bcm2835_spi_reset_hw(ctlr);

	/* and mark as completed */;
	complete(&ctlr->xfer_completion);
}