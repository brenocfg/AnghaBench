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
struct spi_transfer {int dummy; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct bcm2835aux_spi {int /*<<< orphan*/  count_transfer_irq_after_poll; scalar_t__ rx_len; int /*<<< orphan*/  tx_len; int /*<<< orphan*/ * cntl; int /*<<< orphan*/  count_transfer_polling; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL0 ; 
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL1 ; 
 int HZ ; 
 int __bcm2835aux_spi_transfer_one_irq (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 int /*<<< orphan*/  bcm2835aux_spi_transfer_helper (struct bcm2835aux_spi*) ; 
 int /*<<< orphan*/  bcm2835aux_wr (struct bcm2835aux_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int jiffies ; 
 int polling_limit_us ; 
 struct bcm2835aux_spi* spi_master_get_devdata (struct spi_master*) ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static int bcm2835aux_spi_transfer_one_poll(struct spi_master *master,
					    struct spi_device *spi,
					struct spi_transfer *tfr)
{
	struct bcm2835aux_spi *bs = spi_master_get_devdata(master);
	unsigned long timeout;

	/* update statistics */
	bs->count_transfer_polling++;

	/* configure spi */
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, bs->cntl[0]);

	/* set the timeout to at least 2 jiffies */
	timeout = jiffies + 2 + HZ * polling_limit_us / 1000000;

	/* loop until finished the transfer */
	while (bs->rx_len) {

		/* do common fifo handling */
		bcm2835aux_spi_transfer_helper(bs);

		/* there is still data pending to read check the timeout */
		if (bs->rx_len && time_after(jiffies, timeout)) {
			dev_dbg_ratelimited(&spi->dev,
					    "timeout period reached: jiffies: %lu remaining tx/rx: %d/%d - falling back to interrupt mode\n",
					    jiffies - timeout,
					    bs->tx_len, bs->rx_len);
			/* forward to interrupt handler */
			bs->count_transfer_irq_after_poll++;
			return __bcm2835aux_spi_transfer_one_irq(master,
							       spi, tfr);
		}
	}

	/* and return without waiting for completion */
	return 0;
}