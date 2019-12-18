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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct xilinx_spi {int bytes_per_word; scalar_t__ tx_ptr; scalar_t__ regs; int /*<<< orphan*/  (* write_fn ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ XSPI_TXD_OFFSET ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void xilinx_spi_tx(struct xilinx_spi *xspi)
{
	u32 data = 0;

	if (!xspi->tx_ptr) {
		xspi->write_fn(0, xspi->regs + XSPI_TXD_OFFSET);
		return;
	}

	switch (xspi->bytes_per_word) {
	case 1:
		data = *(u8 *)(xspi->tx_ptr);
		break;
	case 2:
		data = *(u16 *)(xspi->tx_ptr);
		break;
	case 4:
		data = *(u32 *)(xspi->tx_ptr);
		break;
	}

	xspi->write_fn(data, xspi->regs + XSPI_TXD_OFFSET);
	xspi->tx_ptr += xspi->bytes_per_word;
}