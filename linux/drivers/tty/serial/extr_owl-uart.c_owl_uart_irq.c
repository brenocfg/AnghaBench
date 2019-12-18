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
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  OWL_UART_STAT ; 
 int OWL_UART_STAT_RIP ; 
 int OWL_UART_STAT_TIP ; 
 int owl_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owl_uart_receive_chars (struct uart_port*) ; 
 int /*<<< orphan*/  owl_uart_send_chars (struct uart_port*) ; 
 int /*<<< orphan*/  owl_uart_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t owl_uart_irq(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned long flags;
	u32 stat;

	spin_lock_irqsave(&port->lock, flags);

	stat = owl_uart_read(port, OWL_UART_STAT);

	if (stat & OWL_UART_STAT_RIP)
		owl_uart_receive_chars(port);

	if (stat & OWL_UART_STAT_TIP)
		owl_uart_send_chars(port);

	stat = owl_uart_read(port, OWL_UART_STAT);
	stat |= OWL_UART_STAT_RIP | OWL_UART_STAT_TIP;
	owl_uart_write(port, stat, OWL_UART_STAT);

	spin_unlock_irqrestore(&port->lock, flags);

	return IRQ_HANDLED;
}