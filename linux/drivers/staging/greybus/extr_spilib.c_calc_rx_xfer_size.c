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
typedef  size_t u32 ;
struct gb_spi_transfer_response {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static size_t calc_rx_xfer_size(u32 rx_size, u32 *tx_xfer_size, u32 len,
				size_t data_max)
{
	size_t rx_xfer_size;

	data_max -= sizeof(struct gb_spi_transfer_response);

	if (rx_size + len > data_max)
		rx_xfer_size = data_max - rx_size;
	else
		rx_xfer_size = len;

	/* if this is a write_read, for symmetry read the same as write */
	if (*tx_xfer_size && rx_xfer_size > *tx_xfer_size)
		rx_xfer_size = *tx_xfer_size;
	if (*tx_xfer_size && rx_xfer_size < *tx_xfer_size)
		*tx_xfer_size = rx_xfer_size;

	return rx_xfer_size;
}