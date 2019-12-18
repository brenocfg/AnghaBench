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
typedef  int u16 ;
struct xilinx_spi {int bytes_per_word; scalar_t__ irq; int buffer_size; int (* read_fn ) (scalar_t__) ;scalar_t__ regs; int /*<<< orphan*/  (* write_fn ) (int,scalar_t__) ;int /*<<< orphan*/  done; int /*<<< orphan*/  rx_ptr; int /*<<< orphan*/  tx_ptr; } ;
struct spi_transfer {int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ XIPIF_V123B_DGIER_OFFSET ; 
 int XIPIF_V123B_GINTR_ENABLE ; 
 scalar_t__ XIPIF_V123B_IISR_OFFSET ; 
 scalar_t__ XSPI_CR_OFFSET ; 
 int XSPI_CR_TRANS_INHIBIT ; 
 scalar_t__ XSPI_SR_OFFSET ; 
 int XSPI_SR_RX_EMPTY_MASK ; 
 int XSPI_SR_TX_EMPTY_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct xilinx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub10 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub11 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int,scalar_t__) ; 
 int stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub6 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub7 (int,scalar_t__) ; 
 int stub8 (scalar_t__) ; 
 int stub9 (scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xilinx_spi_rx (struct xilinx_spi*) ; 
 int /*<<< orphan*/  xilinx_spi_tx (struct xilinx_spi*) ; 
 int /*<<< orphan*/  xspi_init_hw (struct xilinx_spi*) ; 

__attribute__((used)) static int xilinx_spi_txrx_bufs(struct spi_device *spi, struct spi_transfer *t)
{
	struct xilinx_spi *xspi = spi_master_get_devdata(spi->master);
	int remaining_words;	/* the number of words left to transfer */
	bool use_irq = false;
	u16 cr = 0;

	/* We get here with transmitter inhibited */

	xspi->tx_ptr = t->tx_buf;
	xspi->rx_ptr = t->rx_buf;
	remaining_words = t->len / xspi->bytes_per_word;

	if (xspi->irq >= 0 &&  remaining_words > xspi->buffer_size) {
		u32 isr;
		use_irq = true;
		/* Inhibit irq to avoid spurious irqs on tx_empty*/
		cr = xspi->read_fn(xspi->regs + XSPI_CR_OFFSET);
		xspi->write_fn(cr | XSPI_CR_TRANS_INHIBIT,
			       xspi->regs + XSPI_CR_OFFSET);
		/* ACK old irqs (if any) */
		isr = xspi->read_fn(xspi->regs + XIPIF_V123B_IISR_OFFSET);
		if (isr)
			xspi->write_fn(isr,
				       xspi->regs + XIPIF_V123B_IISR_OFFSET);
		/* Enable the global IPIF interrupt */
		xspi->write_fn(XIPIF_V123B_GINTR_ENABLE,
				xspi->regs + XIPIF_V123B_DGIER_OFFSET);
		reinit_completion(&xspi->done);
	}

	while (remaining_words) {
		int n_words, tx_words, rx_words;
		u32 sr;
		int stalled;

		n_words = min(remaining_words, xspi->buffer_size);

		tx_words = n_words;
		while (tx_words--)
			xilinx_spi_tx(xspi);

		/* Start the transfer by not inhibiting the transmitter any
		 * longer
		 */

		if (use_irq) {
			xspi->write_fn(cr, xspi->regs + XSPI_CR_OFFSET);
			wait_for_completion(&xspi->done);
			/* A transmit has just completed. Process received data
			 * and check for more data to transmit. Always inhibit
			 * the transmitter while the Isr refills the transmit
			 * register/FIFO, or make sure it is stopped if we're
			 * done.
			 */
			xspi->write_fn(cr | XSPI_CR_TRANS_INHIBIT,
				       xspi->regs + XSPI_CR_OFFSET);
			sr = XSPI_SR_TX_EMPTY_MASK;
		} else
			sr = xspi->read_fn(xspi->regs + XSPI_SR_OFFSET);

		/* Read out all the data from the Rx FIFO */
		rx_words = n_words;
		stalled = 10;
		while (rx_words) {
			if (rx_words == n_words && !(stalled--) &&
			    !(sr & XSPI_SR_TX_EMPTY_MASK) &&
			    (sr & XSPI_SR_RX_EMPTY_MASK)) {
				dev_err(&spi->dev,
					"Detected stall. Check C_SPI_MODE and C_SPI_MEMORY\n");
				xspi_init_hw(xspi);
				return -EIO;
			}

			if ((sr & XSPI_SR_TX_EMPTY_MASK) && (rx_words > 1)) {
				xilinx_spi_rx(xspi);
				rx_words--;
				continue;
			}

			sr = xspi->read_fn(xspi->regs + XSPI_SR_OFFSET);
			if (!(sr & XSPI_SR_RX_EMPTY_MASK)) {
				xilinx_spi_rx(xspi);
				rx_words--;
			}
		}

		remaining_words -= n_words;
	}

	if (use_irq) {
		xspi->write_fn(0, xspi->regs + XIPIF_V123B_DGIER_OFFSET);
		xspi->write_fn(cr, xspi->regs + XSPI_CR_OFFSET);
	}

	return t->len;
}