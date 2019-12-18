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
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SPRD_ICLR ; 
 int /*<<< orphan*/  SPRD_ICLR_TIMEOUT ; 
 int /*<<< orphan*/  SPRD_IMSR ; 
 unsigned int SPRD_IMSR_BREAK_DETECT ; 
 unsigned int SPRD_IMSR_RX_FIFO_FULL ; 
 unsigned int SPRD_IMSR_TIMEOUT ; 
 unsigned int SPRD_IMSR_TX_FIFO_EMPTY ; 
 unsigned int serial_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprd_rx (struct uart_port*) ; 
 int /*<<< orphan*/  sprd_tx (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t sprd_handle_irq(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned int ims;

	spin_lock(&port->lock);

	ims = serial_in(port, SPRD_IMSR);

	if (!ims) {
		spin_unlock(&port->lock);
		return IRQ_NONE;
	}

	if (ims & SPRD_IMSR_TIMEOUT)
		serial_out(port, SPRD_ICLR, SPRD_ICLR_TIMEOUT);

	if (ims & (SPRD_IMSR_RX_FIFO_FULL | SPRD_IMSR_BREAK_DETECT |
		   SPRD_IMSR_TIMEOUT))
		sprd_rx(port);

	if (ims & SPRD_IMSR_TX_FIFO_EMPTY)
		sprd_tx(port);

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}