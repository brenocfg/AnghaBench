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
typedef  int u32 ;
struct spi_controller {int /*<<< orphan*/  xfer_completion; } ;
struct bcm2835_spi {int /*<<< orphan*/  rx_len; scalar_t__ tx_len; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_DONE ; 
 int BCM2835_SPI_CS_RXF ; 
 int BCM2835_SPI_CS_RXR ; 
 int /*<<< orphan*/  BCM2835_SPI_FIFO_SIZE ; 
 int /*<<< orphan*/  BCM2835_SPI_FIFO_SIZE_3_4 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int bcm2835_rd (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_rd_fifo (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  bcm2835_rd_fifo_blind (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_controller*) ; 
 int /*<<< orphan*/  bcm2835_wr_fifo (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  bcm2835_wr_fifo_blind (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static irqreturn_t bcm2835_spi_interrupt(int irq, void *dev_id)
{
	struct spi_controller *ctlr = dev_id;
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	u32 cs = bcm2835_rd(bs, BCM2835_SPI_CS);

	/*
	 * An interrupt is signaled either if DONE is set (TX FIFO empty)
	 * or if RXR is set (RX FIFO >= ¾ full).
	 */
	if (cs & BCM2835_SPI_CS_RXF)
		bcm2835_rd_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE);
	else if (cs & BCM2835_SPI_CS_RXR)
		bcm2835_rd_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE_3_4);

	if (bs->tx_len && cs & BCM2835_SPI_CS_DONE)
		bcm2835_wr_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE);

	/* Read as many bytes as possible from FIFO */
	bcm2835_rd_fifo(bs);
	/* Write as many bytes as possible to FIFO */
	bcm2835_wr_fifo(bs);

	if (!bs->rx_len) {
		/* Transfer complete - reset SPI HW */
		bcm2835_spi_reset_hw(ctlr);
		/* wake up the framework */
		complete(&ctlr->xfer_completion);
	}

	return IRQ_HANDLED;
}