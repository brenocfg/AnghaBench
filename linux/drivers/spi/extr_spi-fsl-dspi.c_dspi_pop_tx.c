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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_dspi {int bytes_per_word; int len; scalar_t__ tx; } ;

/* Variables and functions */

__attribute__((used)) static u32 dspi_pop_tx(struct fsl_dspi *dspi)
{
	u32 txdata = 0;

	if (dspi->tx) {
		if (dspi->bytes_per_word == 1)
			txdata = *(u8 *)dspi->tx;
		else if (dspi->bytes_per_word == 2)
			txdata = *(u16 *)dspi->tx;
		else  /* dspi->bytes_per_word == 4 */
			txdata = *(u32 *)dspi->tx;
		dspi->tx += dspi->bytes_per_word;
	}
	dspi->len -= dspi->bytes_per_word;
	return txdata;
}