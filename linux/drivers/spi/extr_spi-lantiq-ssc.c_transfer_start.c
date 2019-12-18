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
struct spi_transfer {int len; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;
struct spi_device {int dummy; } ;
struct lantiq_ssc_spi {int tx_todo; int rx_todo; int /*<<< orphan*/  lock; scalar_t__ tx; scalar_t__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  rx_request (struct lantiq_ssc_spi*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_fifo_write (struct lantiq_ssc_spi*) ; 

__attribute__((used)) static int transfer_start(struct lantiq_ssc_spi *spi, struct spi_device *spidev,
			  struct spi_transfer *t)
{
	unsigned long flags;

	spin_lock_irqsave(&spi->lock, flags);

	spi->tx = t->tx_buf;
	spi->rx = t->rx_buf;

	if (t->tx_buf) {
		spi->tx_todo = t->len;

		/* initially fill TX FIFO */
		tx_fifo_write(spi);
	}

	if (spi->rx) {
		spi->rx_todo = t->len;

		/* start shift clock in RX-only mode */
		if (!spi->tx)
			rx_request(spi);
	}

	spin_unlock_irqrestore(&spi->lock, flags);

	return t->len;
}