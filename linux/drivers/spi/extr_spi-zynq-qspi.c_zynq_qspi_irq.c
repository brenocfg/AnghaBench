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
struct zynq_qspi {int /*<<< orphan*/  data_completion; int /*<<< orphan*/  rx_bytes; scalar_t__ tx_bytes; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ZYNQ_QSPI_IDIS_OFFSET ; 
 int ZYNQ_QSPI_IXR_RXNEMTY_MASK ; 
 int ZYNQ_QSPI_IXR_RXTX_MASK ; 
 int ZYNQ_QSPI_IXR_TXNFULL_MASK ; 
 int /*<<< orphan*/  ZYNQ_QSPI_RX_THRESHOLD ; 
 int /*<<< orphan*/  ZYNQ_QSPI_STATUS_OFFSET ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int zynq_qspi_read (struct zynq_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_qspi_read_op (struct zynq_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_qspi_write (struct zynq_qspi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zynq_qspi_write_op (struct zynq_qspi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t zynq_qspi_irq(int irq, void *dev_id)
{
	u32 intr_status;
	bool txempty;
	struct zynq_qspi *xqspi = (struct zynq_qspi *)dev_id;

	intr_status = zynq_qspi_read(xqspi, ZYNQ_QSPI_STATUS_OFFSET);
	zynq_qspi_write(xqspi, ZYNQ_QSPI_STATUS_OFFSET, intr_status);

	if ((intr_status & ZYNQ_QSPI_IXR_TXNFULL_MASK) ||
	    (intr_status & ZYNQ_QSPI_IXR_RXNEMTY_MASK)) {
		/*
		 * This bit is set when Tx FIFO has < THRESHOLD entries.
		 * We have the THRESHOLD value set to 1,
		 * so this bit indicates Tx FIFO is empty.
		 */
		txempty = !!(intr_status & ZYNQ_QSPI_IXR_TXNFULL_MASK);
		/* Read out the data from the RX FIFO */
		zynq_qspi_read_op(xqspi, ZYNQ_QSPI_RX_THRESHOLD);
		if (xqspi->tx_bytes) {
			/* There is more data to send */
			zynq_qspi_write_op(xqspi, ZYNQ_QSPI_RX_THRESHOLD,
					   txempty);
		} else {
			/*
			 * If transfer and receive is completed then only send
			 * complete signal.
			 */
			if (!xqspi->rx_bytes) {
				zynq_qspi_write(xqspi,
						ZYNQ_QSPI_IDIS_OFFSET,
						ZYNQ_QSPI_IXR_RXTX_MASK);
				complete(&xqspi->data_completion);
			}
		}
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}