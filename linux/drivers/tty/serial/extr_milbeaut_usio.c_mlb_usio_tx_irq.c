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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MLB_USIO_REG_SSR ; 
 int MLB_USIO_SSR_TBI ; 
 int /*<<< orphan*/  mlb_usio_tx_chars (struct uart_port*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mlb_usio_tx_irq(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;

	spin_lock(&port->lock);
	if (readb(port->membase + MLB_USIO_REG_SSR) & MLB_USIO_SSR_TBI)
		mlb_usio_tx_chars(port);
	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}