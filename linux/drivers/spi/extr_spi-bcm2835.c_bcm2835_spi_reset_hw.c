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
struct spi_controller {int dummy; } ;
struct bcm2835_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_CLEAR_RX ; 
 int BCM2835_SPI_CS_CLEAR_TX ; 
 int BCM2835_SPI_CS_DMAEN ; 
 int BCM2835_SPI_CS_DONE ; 
 int BCM2835_SPI_CS_INTD ; 
 int BCM2835_SPI_CS_INTR ; 
 int BCM2835_SPI_CS_TA ; 
 int /*<<< orphan*/  BCM2835_SPI_DLEN ; 
 int bcm2835_rd (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static void bcm2835_spi_reset_hw(struct spi_controller *ctlr)
{
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	u32 cs = bcm2835_rd(bs, BCM2835_SPI_CS);

	/* Disable SPI interrupts and transfer */
	cs &= ~(BCM2835_SPI_CS_INTR |
		BCM2835_SPI_CS_INTD |
		BCM2835_SPI_CS_DMAEN |
		BCM2835_SPI_CS_TA);
	/*
	 * Transmission sometimes breaks unless the DONE bit is written at the
	 * end of every transfer.  The spec says it's a RO bit.  Either the
	 * spec is wrong and the bit is actually of type RW1C, or it's a
	 * hardware erratum.
	 */
	cs |= BCM2835_SPI_CS_DONE;
	/* and reset RX/TX FIFOS */
	cs |= BCM2835_SPI_CS_CLEAR_RX | BCM2835_SPI_CS_CLEAR_TX;

	/* and reset the SPI_HW */
	bcm2835_wr(bs, BCM2835_SPI_CS, cs);
	/* as well as DLEN */
	bcm2835_wr(bs, BCM2835_SPI_DLEN, 0);
}