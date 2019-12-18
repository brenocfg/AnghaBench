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
struct spi_controller {int /*<<< orphan*/  xfer_completion; int /*<<< orphan*/  dma_rx; } ;
struct bcm2835_spi {size_t chip_select; int tx_dma_active; int /*<<< orphan*/  rx_dma_active; int /*<<< orphan*/ * clear_rx_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_DONE ; 
 int bcm2835_rd (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_controller*) ; 
 int /*<<< orphan*/  bcm2835_spi_undo_prologue (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_terminate_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static void bcm2835_spi_dma_tx_done(void *data)
{
	struct spi_controller *ctlr = data;
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);

	/* busy-wait for TX FIFO to empty */
	while (!(bcm2835_rd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_DONE))
		bcm2835_wr(bs, BCM2835_SPI_CS,
			   bs->clear_rx_cs[bs->chip_select]);

	bs->tx_dma_active = false;
	smp_wmb();

	/*
	 * In case of a very short transfer, RX DMA may not have been
	 * issued yet.  The onus is then on bcm2835_spi_transfer_one_dma()
	 * to terminate it immediately after issuing.
	 */
	if (cmpxchg(&bs->rx_dma_active, true, false))
		dmaengine_terminate_async(ctlr->dma_rx);

	bcm2835_spi_undo_prologue(bs);
	bcm2835_spi_reset_hw(ctlr);
	complete(&ctlr->xfer_completion);
}