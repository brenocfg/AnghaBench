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
struct gb_spi_transfer_request {int dummy; } ;
struct gb_spi_transfer {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static size_t calc_tx_xfer_size(u32 tx_size, u32 count, size_t len,
				size_t data_max)
{
	size_t headers_size;

	data_max -= sizeof(struct gb_spi_transfer_request);
	headers_size = (count + 1) * sizeof(struct gb_spi_transfer);

	if (tx_size + headers_size + len > data_max)
		return data_max - (tx_size + sizeof(struct gb_spi_transfer));

	return len;
}