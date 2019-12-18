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
struct spi_transfer {scalar_t__ len; } ;
struct gb_spilib {scalar_t__ tx_xfer_offset; scalar_t__ last_xfer_size; scalar_t__ rx_xfer_offset; struct spi_transfer* last_xfer; } ;

/* Variables and functions */

__attribute__((used)) static bool is_last_xfer_done(struct gb_spilib *spi)
{
	struct spi_transfer *last_xfer = spi->last_xfer;

	if ((spi->tx_xfer_offset + spi->last_xfer_size == last_xfer->len) ||
	    (spi->rx_xfer_offset + spi->last_xfer_size == last_xfer->len))
		return true;

	return false;
}