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
struct uart_port {int flags; int iobase; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; int /*<<< orphan*/  irq; } ;
struct uart_8250_port {TYPE_1__* ops; scalar_t__ dma; scalar_t__ ier; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_irq ) (struct uart_8250_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCM_OUT1 ; 
 int /*<<< orphan*/  TIOCM_OUT2 ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_SBC ; 
 int /*<<< orphan*/  UART_RX ; 
 int UPF_FOURPORT ; 
 int /*<<< orphan*/  disable_rsa (struct uart_8250_port*) ; 
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  serial8250_clear_fifos (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_release_dma (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_get (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_put (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_set_mctrl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct uart_8250_port*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

void serial8250_do_shutdown(struct uart_port *port)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned long flags;

	serial8250_rpm_get(up);
	/*
	 * Disable interrupts from this port
	 */
	spin_lock_irqsave(&port->lock, flags);
	up->ier = 0;
	serial_port_out(port, UART_IER, 0);
	spin_unlock_irqrestore(&port->lock, flags);

	synchronize_irq(port->irq);

	if (up->dma)
		serial8250_release_dma(up);

	spin_lock_irqsave(&port->lock, flags);
	if (port->flags & UPF_FOURPORT) {
		/* reset interrupts on the AST Fourport board */
		inb((port->iobase & 0xfe0) | 0x1f);
		port->mctrl |= TIOCM_OUT1;
	} else
		port->mctrl &= ~TIOCM_OUT2;

	serial8250_set_mctrl(port, port->mctrl);
	spin_unlock_irqrestore(&port->lock, flags);

	/*
	 * Disable break condition and FIFOs
	 */
	serial_port_out(port, UART_LCR,
			serial_port_in(port, UART_LCR) & ~UART_LCR_SBC);
	serial8250_clear_fifos(up);

#ifdef CONFIG_SERIAL_8250_RSA
	/*
	 * Reset the RSA board back to 115kbps compat mode.
	 */
	disable_rsa(up);
#endif

	/*
	 * Read data port to reset things, and then unlink from
	 * the IRQ chain.
	 */
	serial_port_in(port, UART_RX);
	serial8250_rpm_put(up);

	up->ops->release_irq(up);
}