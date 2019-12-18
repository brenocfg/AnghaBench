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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OWL_UART_CTL ; 
 int OWL_UART_CTL_EN ; 
 int OWL_UART_CTL_RXDE ; 
 int OWL_UART_CTL_RXIE ; 
 int OWL_UART_CTL_TXDE ; 
 int OWL_UART_CTL_TXIE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int owl_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owl_uart_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void owl_uart_shutdown(struct uart_port *port)
{
	u32 val;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	val = owl_uart_read(port, OWL_UART_CTL);
	val &= ~(OWL_UART_CTL_TXIE | OWL_UART_CTL_RXIE
		| OWL_UART_CTL_TXDE | OWL_UART_CTL_RXDE | OWL_UART_CTL_EN);
	owl_uart_write(port, val, OWL_UART_CTL);

	spin_unlock_irqrestore(&port->lock, flags);

	free_irq(port->irq, port);
}