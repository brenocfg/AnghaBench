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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct spi_controller {int dummy; } ;
struct bcm2835_spi {int /*<<< orphan*/  count_transfer_irq_after_polling; scalar_t__ rx_len; int /*<<< orphan*/  tx_len; int /*<<< orphan*/  count_transfer_polling; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_TA ; 
 int /*<<< orphan*/  BCM2835_SPI_FIFO_SIZE ; 
 int HZ ; 
 int /*<<< orphan*/  bcm2835_rd_fifo (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_controller*) ; 
 int bcm2835_spi_transfer_one_irq (struct spi_controller*,struct spi_device*,struct spi_transfer*,int,int) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm2835_wr_fifo (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  bcm2835_wr_fifo_blind (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int jiffies ; 
 int polling_limit_us ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static int bcm2835_spi_transfer_one_poll(struct spi_controller *ctlr,
					 struct spi_device *spi,
					 struct spi_transfer *tfr,
					 u32 cs)
{
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	unsigned long timeout;

	/* update usage statistics */
	bs->count_transfer_polling++;

	/* enable HW block without interrupts */
	bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA);

	/* fill in the fifo before timeout calculations
	 * if we are interrupted here, then the data is
	 * getting transferred by the HW while we are interrupted
	 */
	bcm2835_wr_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE);

	/* set the timeout to at least 2 jiffies */
	timeout = jiffies + 2 + HZ * polling_limit_us / 1000000;

	/* loop until finished the transfer */
	while (bs->rx_len) {
		/* fill in tx fifo with remaining data */
		bcm2835_wr_fifo(bs);

		/* read from fifo as much as possible */
		bcm2835_rd_fifo(bs);

		/* if there is still data pending to read
		 * then check the timeout
		 */
		if (bs->rx_len && time_after(jiffies, timeout)) {
			dev_dbg_ratelimited(&spi->dev,
					    "timeout period reached: jiffies: %lu remaining tx/rx: %d/%d - falling back to interrupt mode\n",
					    jiffies - timeout,
					    bs->tx_len, bs->rx_len);
			/* fall back to interrupt mode */

			/* update usage statistics */
			bs->count_transfer_irq_after_polling++;

			return bcm2835_spi_transfer_one_irq(ctlr, spi,
							    tfr, cs, false);
		}
	}

	/* Transfer complete - reset SPI HW */
	bcm2835_spi_reset_hw(ctlr);
	/* and return without waiting for completion */
	return 0;
}