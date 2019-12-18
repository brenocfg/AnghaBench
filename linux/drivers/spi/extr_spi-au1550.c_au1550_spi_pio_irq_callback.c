#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct au1550_spi {scalar_t__ rx_count; scalar_t__ len; scalar_t__ tx_count; int /*<<< orphan*/  master_done; TYPE_1__* regs; int /*<<< orphan*/  (* tx_word ) (struct au1550_spi*) ;int /*<<< orphan*/  (* rx_word ) (struct au1550_spi*) ;int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int psc_spistat; int psc_spievent; int /*<<< orphan*/  psc_spipcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PSC_SPIEVNT_MD ; 
 int PSC_SPIEVNT_MM ; 
 int PSC_SPIEVNT_RO ; 
 int PSC_SPIEVNT_RR ; 
 int PSC_SPIEVNT_RU ; 
 int PSC_SPIEVNT_SD ; 
 int PSC_SPIEVNT_TO ; 
 int PSC_SPIEVNT_TR ; 
 int PSC_SPIEVNT_TU ; 
 int /*<<< orphan*/  PSC_SPIPCR_MS ; 
 int PSC_SPISTAT_DI ; 
 int PSC_SPISTAT_RE ; 
 int PSC_SPISTAT_TF ; 
 int /*<<< orphan*/  au1550_spi_mask_ack_all (struct au1550_spi*) ; 
 int /*<<< orphan*/  au1550_spi_reset_fifos (struct au1550_spi*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct au1550_spi*) ; 
 int /*<<< orphan*/  stub2 (struct au1550_spi*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static irqreturn_t au1550_spi_pio_irq_callback(struct au1550_spi *hw)
{
	int busy;
	u32 stat, evnt;

	stat = hw->regs->psc_spistat;
	evnt = hw->regs->psc_spievent;
	wmb(); /* drain writebuffer */
	if ((stat & PSC_SPISTAT_DI) == 0) {
		dev_err(hw->dev, "Unexpected IRQ!\n");
		return IRQ_NONE;
	}

	if ((evnt & (PSC_SPIEVNT_MM | PSC_SPIEVNT_RO
				| PSC_SPIEVNT_RU | PSC_SPIEVNT_TO
				| PSC_SPIEVNT_SD))
			!= 0) {
		/*
		 * due to an error we consider transfer as done,
		 * so mask all events until before next transfer start
		 */
		au1550_spi_mask_ack_all(hw);
		au1550_spi_reset_fifos(hw);
		dev_err(hw->dev,
			"pio transfer: unexpected SPI error "
			"(event=0x%x stat=0x%x)!\n", evnt, stat);
		complete(&hw->master_done);
		return IRQ_HANDLED;
	}

	/*
	 * while there is something to read from rx fifo
	 * or there is a space to write to tx fifo:
	 */
	do {
		busy = 0;
		stat = hw->regs->psc_spistat;
		wmb(); /* drain writebuffer */

		/*
		 * Take care to not let the Rx FIFO overflow.
		 *
		 * We only write a byte if we have read one at least. Initially,
		 * the write fifo is full, so we should read from the read fifo
		 * first.
		 * In case we miss a word from the read fifo, we should get a
		 * RO event and should back out.
		 */
		if (!(stat & PSC_SPISTAT_RE) && hw->rx_count < hw->len) {
			hw->rx_word(hw);
			busy = 1;

			if (!(stat & PSC_SPISTAT_TF) && hw->tx_count < hw->len)
				hw->tx_word(hw);
		}
	} while (busy);

	hw->regs->psc_spievent = PSC_SPIEVNT_RR | PSC_SPIEVNT_TR;
	wmb(); /* drain writebuffer */

	/*
	 * Restart the SPI transmission in case of a transmit underflow.
	 * This seems to work despite the notes in the Au1550 data book
	 * of Figure 8-4 with flowchart for SPI master operation:
	 *
	 * """Note 1: An XFR Error Interrupt occurs, unless masked,
	 * for any of the following events: Tx FIFO Underflow,
	 * Rx FIFO Overflow, or Multiple-master Error
	 *    Note 2: In case of a Tx Underflow Error, all zeroes are
	 * transmitted."""
	 *
	 * By simply restarting the spi transfer on Tx Underflow Error,
	 * we assume that spi transfer was paused instead of zeroes
	 * transmittion mentioned in the Note 2 of Au1550 data book.
	 */
	if (evnt & PSC_SPIEVNT_TU) {
		hw->regs->psc_spievent = PSC_SPIEVNT_TU | PSC_SPIEVNT_MD;
		wmb(); /* drain writebuffer */
		hw->regs->psc_spipcr = PSC_SPIPCR_MS;
		wmb(); /* drain writebuffer */
	}

	if (hw->rx_count >= hw->len) {
		/* transfer completed successfully */
		au1550_spi_mask_ack_all(hw);
		complete(&hw->master_done);
	}
	return IRQ_HANDLED;
}