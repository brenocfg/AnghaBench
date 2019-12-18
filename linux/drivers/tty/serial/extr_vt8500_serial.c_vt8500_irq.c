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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long RX_FIFO_INTS ; 
 unsigned long TCTS ; 
 unsigned long TX_FIFO_INTS ; 
 int /*<<< orphan*/  VT8500_URISR ; 
 int /*<<< orphan*/  handle_delta_cts (struct uart_port*) ; 
 int /*<<< orphan*/  handle_rx (struct uart_port*) ; 
 int /*<<< orphan*/  handle_tx (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long vt8500_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt8500_write (struct uart_port*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t vt8500_irq(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned long isr;

	spin_lock(&port->lock);
	isr = vt8500_read(port, VT8500_URISR);

	/* Acknowledge active status bits */
	vt8500_write(port, isr, VT8500_URISR);

	if (isr & RX_FIFO_INTS)
		handle_rx(port);
	if (isr & TX_FIFO_INTS)
		handle_tx(port);
	if (isr & TCTS)
		handle_delta_cts(port);

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}