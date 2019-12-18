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
struct spi_transfer {scalar_t__ tx_buf; scalar_t__ rx_buf; scalar_t__ len; } ;
struct spi_statistics {int /*<<< orphan*/  lock; int /*<<< orphan*/  bytes_rx; int /*<<< orphan*/  bytes_tx; int /*<<< orphan*/  bytes; int /*<<< orphan*/ * transfer_bytes_histo; int /*<<< orphan*/  transfers; } ;
struct spi_controller {scalar_t__ dummy_tx; scalar_t__ dummy_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_STATISTICS_HISTO_SIZE ; 
 int /*<<< orphan*/  fls (scalar_t__) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void spi_statistics_add_transfer_stats(struct spi_statistics *stats,
				       struct spi_transfer *xfer,
				       struct spi_controller *ctlr)
{
	unsigned long flags;
	int l2len = min(fls(xfer->len), SPI_STATISTICS_HISTO_SIZE) - 1;

	if (l2len < 0)
		l2len = 0;

	spin_lock_irqsave(&stats->lock, flags);

	stats->transfers++;
	stats->transfer_bytes_histo[l2len]++;

	stats->bytes += xfer->len;
	if ((xfer->tx_buf) &&
	    (xfer->tx_buf != ctlr->dummy_tx))
		stats->bytes_tx += xfer->len;
	if ((xfer->rx_buf) &&
	    (xfer->rx_buf != ctlr->dummy_rx))
		stats->bytes_rx += xfer->len;

	spin_unlock_irqrestore(&stats->lock, flags);
}