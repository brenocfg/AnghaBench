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
struct spi_transfer {unsigned int len; scalar_t__ rx_nbits; } ;
struct spi_device {int /*<<< orphan*/  chip_select; int /*<<< orphan*/  master; } ;
struct fsl_espi {unsigned int rxskip; int /*<<< orphan*/  dev; int /*<<< orphan*/  done; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESPI_SPCOM ; 
 int /*<<< orphan*/  ESPI_SPIM ; 
 int ETIMEDOUT ; 
 unsigned int FSL_ESPI_FIFO_SIZE ; 
 int HZ ; 
 int /*<<< orphan*/  SPCOM_CS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPCOM_DO ; 
 int /*<<< orphan*/  SPCOM_RXSKIP (unsigned int) ; 
 int /*<<< orphan*/  SPCOM_TRANLEN (unsigned int) ; 
 int /*<<< orphan*/  SPIM_DON ; 
 int /*<<< orphan*/  SPIM_RXT ; 
 scalar_t__ SPI_NBITS_DUAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fsl_espi_fill_tx_fifo (struct fsl_espi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_espi_write_reg (struct fsl_espi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct fsl_espi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fsl_espi_bufs(struct spi_device *spi, struct spi_transfer *t)
{
	struct fsl_espi *espi = spi_master_get_devdata(spi->master);
	unsigned int rx_len = t->len;
	u32 mask, spcom;
	int ret;

	reinit_completion(&espi->done);

	/* Set SPCOM[CS] and SPCOM[TRANLEN] field */
	spcom = SPCOM_CS(spi->chip_select);
	spcom |= SPCOM_TRANLEN(t->len - 1);

	/* configure RXSKIP mode */
	if (espi->rxskip) {
		spcom |= SPCOM_RXSKIP(espi->rxskip);
		rx_len = t->len - espi->rxskip;
		if (t->rx_nbits == SPI_NBITS_DUAL)
			spcom |= SPCOM_DO;
	}

	fsl_espi_write_reg(espi, ESPI_SPCOM, spcom);

	/* enable interrupts */
	mask = SPIM_DON;
	if (rx_len > FSL_ESPI_FIFO_SIZE)
		mask |= SPIM_RXT;
	fsl_espi_write_reg(espi, ESPI_SPIM, mask);

	/* Prevent filling the fifo from getting interrupted */
	spin_lock_irq(&espi->lock);
	fsl_espi_fill_tx_fifo(espi, 0);
	spin_unlock_irq(&espi->lock);

	/* Won't hang up forever, SPI bus sometimes got lost interrupts... */
	ret = wait_for_completion_timeout(&espi->done, 2 * HZ);
	if (ret == 0)
		dev_err(espi->dev, "Transfer timed out!\n");

	/* disable rx ints */
	fsl_espi_write_reg(espi, ESPI_SPIM, 0);

	return ret == 0 ? -ETIMEDOUT : 0;
}