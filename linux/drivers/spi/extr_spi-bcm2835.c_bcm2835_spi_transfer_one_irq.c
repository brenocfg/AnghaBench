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
struct spi_transfer {int dummy; } ;
struct spi_device {int dummy; } ;
struct spi_controller {int dummy; } ;
struct bcm2835_spi {int /*<<< orphan*/  count_transfer_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_INTD ; 
 int BCM2835_SPI_CS_INTR ; 
 int BCM2835_SPI_CS_TA ; 
 int /*<<< orphan*/  BCM2835_SPI_FIFO_SIZE ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm2835_wr_fifo (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  bcm2835_wr_fifo_blind (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int bcm2835_spi_transfer_one_irq(struct spi_controller *ctlr,
					struct spi_device *spi,
					struct spi_transfer *tfr,
					u32 cs, bool fifo_empty)
{
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);

	/* update usage statistics */
	bs->count_transfer_irq++;

	/*
	 * Enable HW block, but with interrupts still disabled.
	 * Otherwise the empty TX FIFO would immediately trigger an interrupt.
	 */
	bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA);

	/* fill TX FIFO as much as possible */
	if (fifo_empty)
		bcm2835_wr_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE);
	bcm2835_wr_fifo(bs);

	/* enable interrupts */
	cs |= BCM2835_SPI_CS_INTR | BCM2835_SPI_CS_INTD | BCM2835_SPI_CS_TA;
	bcm2835_wr(bs, BCM2835_SPI_CS, cs);

	/* signal that we need to wait for completion */
	return 1;
}