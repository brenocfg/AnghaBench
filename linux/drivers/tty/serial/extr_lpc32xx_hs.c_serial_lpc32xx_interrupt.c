#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  brk; } ;
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  membase; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LPC32XX_HSUART_IIR (int /*<<< orphan*/ ) ; 
 int LPC32XX_HSU_BRK_INT ; 
 int LPC32XX_HSU_FE_INT ; 
 int LPC32XX_HSU_RX_OE_INT ; 
 int LPC32XX_HSU_RX_TIMEOUT_INT ; 
 int LPC32XX_HSU_RX_TRIG_INT ; 
 int LPC32XX_HSU_TX_INT ; 
 int /*<<< orphan*/  TTY_OVERRUN ; 
 int /*<<< orphan*/  __serial_lpc32xx_rx (struct uart_port*) ; 
 int /*<<< orphan*/  __serial_lpc32xx_tx (struct uart_port*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_schedule_flip (struct tty_port*) ; 
 int /*<<< orphan*/  uart_handle_break (struct uart_port*) ; 
 int /*<<< orphan*/  uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t serial_lpc32xx_interrupt(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	struct tty_port *tport = &port->state->port;
	u32 status;

	spin_lock(&port->lock);

	/* Read UART status and clear latched interrupts */
	status = readl(LPC32XX_HSUART_IIR(port->membase));

	if (status & LPC32XX_HSU_BRK_INT) {
		/* Break received */
		writel(LPC32XX_HSU_BRK_INT, LPC32XX_HSUART_IIR(port->membase));
		port->icount.brk++;
		uart_handle_break(port);
	}

	/* Framing error */
	if (status & LPC32XX_HSU_FE_INT)
		writel(LPC32XX_HSU_FE_INT, LPC32XX_HSUART_IIR(port->membase));

	if (status & LPC32XX_HSU_RX_OE_INT) {
		/* Receive FIFO overrun */
		writel(LPC32XX_HSU_RX_OE_INT,
		       LPC32XX_HSUART_IIR(port->membase));
		port->icount.overrun++;
		tty_insert_flip_char(tport, 0, TTY_OVERRUN);
		tty_schedule_flip(tport);
	}

	/* Data received? */
	if (status & (LPC32XX_HSU_RX_TIMEOUT_INT | LPC32XX_HSU_RX_TRIG_INT))
		__serial_lpc32xx_rx(port);

	/* Transmit data request? */
	if ((status & LPC32XX_HSU_TX_INT) && (!uart_tx_stopped(port))) {
		writel(LPC32XX_HSU_TX_INT, LPC32XX_HSUART_IIR(port->membase));
		__serial_lpc32xx_tx(port);
	}

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}