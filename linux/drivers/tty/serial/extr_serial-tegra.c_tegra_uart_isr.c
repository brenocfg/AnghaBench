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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct tegra_uart_port {unsigned long ier_shadow; int /*<<< orphan*/  use_rx_pio; scalar_t__ rx_in_progress; struct uart_port uport; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long TEGRA_UART_IER_EORD ; 
 int /*<<< orphan*/  UART_IER ; 
 unsigned long UART_IER_RDI ; 
 unsigned long UART_IER_RLSI ; 
 unsigned long UART_IER_RTOIE ; 
 unsigned long UART_IER_THRI ; 
 int /*<<< orphan*/  UART_IIR ; 
 unsigned long UART_IIR_NO_INT ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  do_handle_rx_pio (struct tegra_uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_uart_decode_rx_error (struct tegra_uart_port*,unsigned long) ; 
 int /*<<< orphan*/  tegra_uart_handle_modem_signal_change (struct uart_port*) ; 
 int /*<<< orphan*/  tegra_uart_handle_rx_dma (struct tegra_uart_port*) ; 
 int /*<<< orphan*/  tegra_uart_handle_tx_pio (struct tegra_uart_port*) ; 
 unsigned long tegra_uart_read (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_uart_write (struct tegra_uart_port*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tegra_uart_isr(int irq, void *data)
{
	struct tegra_uart_port *tup = data;
	struct uart_port *u = &tup->uport;
	unsigned long iir;
	unsigned long ier;
	bool is_rx_int = false;
	unsigned long flags;

	spin_lock_irqsave(&u->lock, flags);
	while (1) {
		iir = tegra_uart_read(tup, UART_IIR);
		if (iir & UART_IIR_NO_INT) {
			if (!tup->use_rx_pio && is_rx_int) {
				tegra_uart_handle_rx_dma(tup);
				if (tup->rx_in_progress) {
					ier = tup->ier_shadow;
					ier |= (UART_IER_RLSI | UART_IER_RTOIE |
						TEGRA_UART_IER_EORD);
					tup->ier_shadow = ier;
					tegra_uart_write(tup, ier, UART_IER);
				}
			}
			spin_unlock_irqrestore(&u->lock, flags);
			return IRQ_HANDLED;
		}

		switch ((iir >> 1) & 0x7) {
		case 0: /* Modem signal change interrupt */
			tegra_uart_handle_modem_signal_change(u);
			break;

		case 1: /* Transmit interrupt only triggered when using PIO */
			tup->ier_shadow &= ~UART_IER_THRI;
			tegra_uart_write(tup, tup->ier_shadow, UART_IER);
			tegra_uart_handle_tx_pio(tup);
			break;

		case 4: /* End of data */
		case 6: /* Rx timeout */
		case 2: /* Receive */
			if (!tup->use_rx_pio && !is_rx_int) {
				is_rx_int = true;
				/* Disable Rx interrupts */
				ier = tup->ier_shadow;
				ier |= UART_IER_RDI;
				tegra_uart_write(tup, ier, UART_IER);
				ier &= ~(UART_IER_RDI | UART_IER_RLSI |
					UART_IER_RTOIE | TEGRA_UART_IER_EORD);
				tup->ier_shadow = ier;
				tegra_uart_write(tup, ier, UART_IER);
			} else {
				do_handle_rx_pio(tup);
			}
			break;

		case 3: /* Receive error */
			tegra_uart_decode_rx_error(tup,
					tegra_uart_read(tup, UART_LSR));
			break;

		case 5: /* break nothing to handle */
		case 7: /* break nothing to handle */
			break;
		}
	}
}