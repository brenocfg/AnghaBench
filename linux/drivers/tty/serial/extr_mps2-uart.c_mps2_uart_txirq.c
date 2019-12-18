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
typedef  int u8 ;
struct uart_port {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  UARTn_INT ; 
 int UARTn_INT_TX ; 
 int mps2_uart_read8 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps2_uart_tx_chars (struct uart_port*) ; 
 int /*<<< orphan*/  mps2_uart_write8 (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t mps2_uart_txirq(int irq, void *data)
{
	struct uart_port *port = data;
	u8 irqflag = mps2_uart_read8(port, UARTn_INT);

	if (unlikely(!(irqflag & UARTn_INT_TX)))
		return IRQ_NONE;

	spin_lock(&port->lock);

	mps2_uart_write8(port, UARTn_INT_TX, UARTn_INT);
	mps2_uart_tx_chars(port);

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}