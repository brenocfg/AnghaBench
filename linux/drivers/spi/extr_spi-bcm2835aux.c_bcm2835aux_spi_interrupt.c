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
struct spi_master {int /*<<< orphan*/  xfer_completion; } ;
struct bcm2835aux_spi {int* cntl; int /*<<< orphan*/  rx_len; int /*<<< orphan*/  tx_len; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL1 ; 
 int BCM2835_AUX_SPI_CNTL1_IDLE ; 
 int BCM2835_AUX_SPI_CNTL1_TXEMPTY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int bcm2835aux_rd (struct bcm2835aux_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835aux_spi_transfer_helper (struct bcm2835aux_spi*) ; 
 int /*<<< orphan*/  bcm2835aux_wr (struct bcm2835aux_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct bcm2835aux_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static irqreturn_t bcm2835aux_spi_interrupt(int irq, void *dev_id)
{
	struct spi_master *master = dev_id;
	struct bcm2835aux_spi *bs = spi_master_get_devdata(master);

	/* IRQ may be shared, so return if our interrupts are disabled */
	if (!(bcm2835aux_rd(bs, BCM2835_AUX_SPI_CNTL1) &
	      (BCM2835_AUX_SPI_CNTL1_TXEMPTY | BCM2835_AUX_SPI_CNTL1_IDLE)))
		return IRQ_NONE;

	/* do common fifo handling */
	bcm2835aux_spi_transfer_helper(bs);

	if (!bs->tx_len) {
		/* disable tx fifo empty interrupt */
		bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1] |
			BCM2835_AUX_SPI_CNTL1_IDLE);
	}

	/* and if rx_len is 0 then disable interrupts and wake up completion */
	if (!bs->rx_len) {
		bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
		complete(&master->xfer_completion);
	}

	return IRQ_HANDLED;
}