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
struct uart_port {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_INTEN ; 
 int ASC_INTEN_THE ; 
 int /*<<< orphan*/  ASC_STA ; 
 int ASC_STA_RBF ; 
 int ASC_STA_THE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int asc_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asc_receive_chars (struct uart_port*) ; 
 int /*<<< orphan*/  asc_transmit_chars (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t asc_interrupt(int irq, void *ptr)
{
	struct uart_port *port = ptr;
	u32 status;

	spin_lock(&port->lock);

	status = asc_in(port, ASC_STA);

	if (status & ASC_STA_RBF) {
		/* Receive FIFO not empty */
		asc_receive_chars(port);
	}

	if ((status & ASC_STA_THE) &&
	    (asc_in(port, ASC_INTEN) & ASC_INTEN_THE)) {
		/* Transmitter FIFO at least half empty */
		asc_transmit_chars(port);
	}

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}