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
struct zynq_qspi {unsigned int txbuf; unsigned int tx_bytes; } ;

/* Variables and functions */
#define  ZYNQ_QSPI_TXD_00_00_OFFSET 131 
#define  ZYNQ_QSPI_TXD_00_01_OFFSET 130 
#define  ZYNQ_QSPI_TXD_00_10_OFFSET 129 
#define  ZYNQ_QSPI_TXD_00_11_OFFSET 128 
 int /*<<< orphan*/  memcpy (int*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  zynq_qspi_write (struct zynq_qspi*,unsigned int const,int) ; 

__attribute__((used)) static void zynq_qspi_txfifo_op(struct zynq_qspi *xqspi, unsigned int size)
{
	static const unsigned int offset[4] = {
		ZYNQ_QSPI_TXD_00_01_OFFSET, ZYNQ_QSPI_TXD_00_10_OFFSET,
		ZYNQ_QSPI_TXD_00_11_OFFSET, ZYNQ_QSPI_TXD_00_00_OFFSET };
	u32 data;

	if (xqspi->txbuf) {
		data = 0xffffffff;
		memcpy(&data, xqspi->txbuf, size);
		xqspi->txbuf += size;
	} else {
		data = 0;
	}

	xqspi->tx_bytes -= size;
	zynq_qspi_write(xqspi, offset[size - 1], data);
}