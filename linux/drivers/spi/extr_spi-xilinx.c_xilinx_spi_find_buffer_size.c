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
typedef  int u8 ;
struct xilinx_spi {int (* read_fn ) (scalar_t__) ;scalar_t__ regs; int /*<<< orphan*/  (* write_fn ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ XIPIF_V123B_RESETR_OFFSET ; 
 int /*<<< orphan*/  XIPIF_V123B_RESET_MASK ; 
 scalar_t__ XSPI_SR_OFFSET ; 
 int XSPI_SR_TX_FULL_MASK ; 
 scalar_t__ XSPI_TXD_OFFSET ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int stub3 (scalar_t__) ; 

__attribute__((used)) static int xilinx_spi_find_buffer_size(struct xilinx_spi *xspi)
{
	u8 sr;
	int n_words = 0;

	/*
	 * Before the buffer_size detection we reset the core
	 * to make sure we start with a clean state.
	 */
	xspi->write_fn(XIPIF_V123B_RESET_MASK,
		xspi->regs + XIPIF_V123B_RESETR_OFFSET);

	/* Fill the Tx FIFO with as many words as possible */
	do {
		xspi->write_fn(0, xspi->regs + XSPI_TXD_OFFSET);
		sr = xspi->read_fn(xspi->regs + XSPI_SR_OFFSET);
		n_words++;
	} while (!(sr & XSPI_SR_TX_FULL_MASK));

	return n_words;
}