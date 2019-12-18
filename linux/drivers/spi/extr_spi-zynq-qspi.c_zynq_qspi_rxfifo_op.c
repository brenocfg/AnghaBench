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
struct zynq_qspi {scalar_t__ rx_bytes; scalar_t__ rxbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZYNQ_QSPI_RXD_OFFSET ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  zynq_qspi_read (struct zynq_qspi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zynq_qspi_rxfifo_op(struct zynq_qspi *xqspi, unsigned int size)
{
	u32 data;

	data = zynq_qspi_read(xqspi, ZYNQ_QSPI_RXD_OFFSET);

	if (xqspi->rxbuf) {
		memcpy(xqspi->rxbuf, ((u8 *)&data) + 4 - size, size);
		xqspi->rxbuf += size;
	}

	xqspi->rx_bytes -= size;
	if (xqspi->rx_bytes < 0)
		xqspi->rx_bytes = 0;
}