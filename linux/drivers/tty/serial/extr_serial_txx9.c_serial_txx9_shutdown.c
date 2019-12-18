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
struct TYPE_4__ {scalar_t__ line; int /*<<< orphan*/  irq; TYPE_1__* cons; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; } ;
struct uart_txx9_port {TYPE_2__ port; } ;
struct uart_port {int dummy; } ;
struct TYPE_3__ {scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXX9_SIDICR ; 
 int /*<<< orphan*/  TXX9_SIFCR ; 
 int TXX9_SIFCR_FRSTE ; 
 int TXX9_SIFCR_RFRST ; 
 int TXX9_SIFCR_TFRST ; 
 int /*<<< orphan*/  TXX9_SIFLCR ; 
 int TXX9_SIFLCR_RSDE ; 
 int TXX9_SIFLCR_TBRK ; 
 int TXX9_SIFLCR_TSDE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_txx9_port*) ; 
 int /*<<< orphan*/  serial_txx9_set_mctrl (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_mask (struct uart_txx9_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sio_out (struct uart_txx9_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_set (struct uart_txx9_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_txx9_port* to_uart_txx9_port (struct uart_port*) ; 

__attribute__((used)) static void serial_txx9_shutdown(struct uart_port *port)
{
	struct uart_txx9_port *up = to_uart_txx9_port(port);
	unsigned long flags;

	/*
	 * Disable interrupts from this port
	 */
	sio_out(up, TXX9_SIDICR, 0);	/* disable all intrs */

	spin_lock_irqsave(&up->port.lock, flags);
	serial_txx9_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Disable break condition
	 */
	sio_mask(up, TXX9_SIFLCR, TXX9_SIFLCR_TBRK);

#ifdef CONFIG_SERIAL_TXX9_CONSOLE
	if (up->port.cons && up->port.line == up->port.cons->index) {
		free_irq(up->port.irq, up);
		return;
	}
#endif
	/* reset FIFOs */
	sio_set(up, TXX9_SIFCR,
		TXX9_SIFCR_TFRST | TXX9_SIFCR_RFRST | TXX9_SIFCR_FRSTE);
	/* clear reset */
	sio_mask(up, TXX9_SIFCR,
		 TXX9_SIFCR_TFRST | TXX9_SIFCR_RFRST | TXX9_SIFCR_FRSTE);

	/* Disable RX/TX */
	sio_set(up, TXX9_SIFLCR, TXX9_SIFLCR_RSDE | TXX9_SIFLCR_TSDE);

	free_irq(up->port.irq, up);
}