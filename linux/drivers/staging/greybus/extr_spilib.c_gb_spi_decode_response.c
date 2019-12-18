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
typedef  scalar_t__ u32 ;
struct spi_transfer {scalar_t__ rx_buf; scalar_t__ len; } ;
struct spi_message {int dummy; } ;
struct gb_spilib {struct spi_transfer* last_xfer; scalar_t__ rx_xfer_offset; scalar_t__ last_xfer_size; struct spi_transfer* first_xfer; } ;
struct gb_spi_transfer_response {void* data; } ;

/* Variables and functions */
 struct spi_transfer* list_next_entry (struct spi_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,scalar_t__) ; 
 int /*<<< orphan*/  transfer_list ; 

__attribute__((used)) static void gb_spi_decode_response(struct gb_spilib *spi,
				   struct spi_message *msg,
				   struct gb_spi_transfer_response *response)
{
	struct spi_transfer *xfer = spi->first_xfer;
	void *rx_data = response->data;
	u32 xfer_len;

	while (xfer) {
		/* Copy rx data */
		if (xfer->rx_buf) {
			if (xfer == spi->first_xfer)
				xfer_len = xfer->len - spi->rx_xfer_offset;
			else if (xfer == spi->last_xfer)
				xfer_len = spi->last_xfer_size;
			else
				xfer_len = xfer->len;

			memcpy(xfer->rx_buf + spi->rx_xfer_offset, rx_data,
			       xfer_len);
			rx_data += xfer_len;
		}

		if (xfer == spi->last_xfer)
			break;

		xfer = list_next_entry(xfer, transfer_list);
	}
}