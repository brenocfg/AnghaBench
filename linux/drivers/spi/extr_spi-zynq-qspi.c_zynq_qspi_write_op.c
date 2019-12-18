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
struct zynq_qspi {int tx_bytes; scalar_t__ regs; scalar_t__ txbuf; } ;

/* Variables and functions */
 scalar_t__ ZYNQ_QSPI_TXD_00_00_OFFSET ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zynq_qspi_txfifo_op (struct zynq_qspi*,int) ; 

__attribute__((used)) static void zynq_qspi_write_op(struct zynq_qspi *xqspi, int txcount,
			       bool txempty)
{
	int count, len, k;

	len = xqspi->tx_bytes;
	if (len && len < 4) {
		/*
		 * We must empty the TxFIFO between accesses to TXD0,
		 * TXD1, TXD2, TXD3.
		 */
		if (txempty)
			zynq_qspi_txfifo_op(xqspi, len);

		return;
	}

	count = len / 4;
	if (count > txcount)
		count = txcount;

	if (xqspi->txbuf) {
		iowrite32_rep(xqspi->regs + ZYNQ_QSPI_TXD_00_00_OFFSET,
			      xqspi->txbuf, count);
		xqspi->txbuf += count * 4;
	} else {
		for (k = 0; k < count; k++)
			writel_relaxed(0, xqspi->regs +
					  ZYNQ_QSPI_TXD_00_00_OFFSET);
	}

	xqspi->tx_bytes -= count * 4;
}