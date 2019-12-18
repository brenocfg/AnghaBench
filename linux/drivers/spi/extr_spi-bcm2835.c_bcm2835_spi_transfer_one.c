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
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {unsigned long speed_hz; unsigned long len; scalar_t__ rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {size_t chip_select; int mode; } ;
struct spi_controller {scalar_t__ can_dma; } ;
struct bcm2835_spi {unsigned long tx_len; unsigned long rx_len; scalar_t__ rx_buf; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  clk; int /*<<< orphan*/ * prepare_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CLK ; 
 int /*<<< orphan*/  BCM2835_SPI_CS_REN ; 
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int SPI_3WIRE ; 
 scalar_t__ bcm2835_spi_can_dma (struct spi_controller*,struct spi_device*,struct spi_transfer*) ; 
 int bcm2835_spi_transfer_one_dma (struct spi_controller*,struct spi_device*,struct spi_transfer*,int /*<<< orphan*/ ) ; 
 int bcm2835_spi_transfer_one_irq (struct spi_controller*,struct spi_device*,struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int bcm2835_spi_transfer_one_poll (struct spi_controller*,struct spi_device*,struct spi_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int polling_limit_us ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int bcm2835_spi_transfer_one(struct spi_controller *ctlr,
				    struct spi_device *spi,
				    struct spi_transfer *tfr)
{
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	unsigned long spi_hz, clk_hz, cdiv, spi_used_hz;
	unsigned long hz_per_byte, byte_limit;
	u32 cs = bs->prepare_cs[spi->chip_select];

	/* set clock */
	spi_hz = tfr->speed_hz;
	clk_hz = clk_get_rate(bs->clk);

	if (spi_hz >= clk_hz / 2) {
		cdiv = 2; /* clk_hz/2 is the fastest we can go */
	} else if (spi_hz) {
		/* CDIV must be a multiple of two */
		cdiv = DIV_ROUND_UP(clk_hz, spi_hz);
		cdiv += (cdiv % 2);

		if (cdiv >= 65536)
			cdiv = 0; /* 0 is the slowest we can go */
	} else {
		cdiv = 0; /* 0 is the slowest we can go */
	}
	spi_used_hz = cdiv ? (clk_hz / cdiv) : (clk_hz / 65536);
	bcm2835_wr(bs, BCM2835_SPI_CLK, cdiv);

	/* handle all the 3-wire mode */
	if (spi->mode & SPI_3WIRE && tfr->rx_buf)
		cs |= BCM2835_SPI_CS_REN;

	/* set transmit buffers and length */
	bs->tx_buf = tfr->tx_buf;
	bs->rx_buf = tfr->rx_buf;
	bs->tx_len = tfr->len;
	bs->rx_len = tfr->len;

	/* Calculate the estimated time in us the transfer runs.  Note that
	 * there is 1 idle clocks cycles after each byte getting transferred
	 * so we have 9 cycles/byte.  This is used to find the number of Hz
	 * per byte per polling limit.  E.g., we can transfer 1 byte in 30 us
	 * per 300,000 Hz of bus clock.
	 */
	hz_per_byte = polling_limit_us ? (9 * 1000000) / polling_limit_us : 0;
	byte_limit = hz_per_byte ? spi_used_hz / hz_per_byte : 1;

	/* run in polling mode for short transfers */
	if (tfr->len < byte_limit)
		return bcm2835_spi_transfer_one_poll(ctlr, spi, tfr, cs);

	/* run in dma mode if conditions are right
	 * Note that unlike poll or interrupt mode DMA mode does not have
	 * this 1 idle clock cycle pattern but runs the spi clock without gaps
	 */
	if (ctlr->can_dma && bcm2835_spi_can_dma(ctlr, spi, tfr))
		return bcm2835_spi_transfer_one_dma(ctlr, spi, tfr, cs);

	/* run in interrupt-mode */
	return bcm2835_spi_transfer_one_irq(ctlr, spi, tfr, cs, true);
}