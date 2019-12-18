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
struct spi_message {struct spi_device* spi; } ;
struct spi_device {size_t chip_select; } ;
struct spi_controller {scalar_t__ can_dma; } ;
struct bcm2835_spi {int /*<<< orphan*/ * prepare_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 
 int spi_split_transfers_maxsize (struct spi_controller*,struct spi_message*,int,int) ; 

__attribute__((used)) static int bcm2835_spi_prepare_message(struct spi_controller *ctlr,
				       struct spi_message *msg)
{
	struct spi_device *spi = msg->spi;
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	int ret;

	if (ctlr->can_dma) {
		/*
		 * DMA transfers are limited to 16 bit (0 to 65535 bytes) by
		 * the SPI HW due to DLEN. Split up transfers (32-bit FIFO
		 * aligned) if the limit is exceeded.
		 */
		ret = spi_split_transfers_maxsize(ctlr, msg, 65532,
						  GFP_KERNEL | GFP_DMA);
		if (ret)
			return ret;
	}

	/*
	 * Set up clock polarity before spi_transfer_one_message() asserts
	 * chip select to avoid a gratuitous clock signal edge.
	 */
	bcm2835_wr(bs, BCM2835_SPI_CS, bs->prepare_cs[spi->chip_select]);

	return 0;
}