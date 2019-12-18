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

/* Variables and functions */
 int /*<<< orphan*/  OWL_UART_STAT ; 
 int OWL_UART_STAT_TFES ; 
 unsigned int TIOCSER_TEMT ; 
 int owl_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int owl_uart_tx_empty(struct uart_port *port)
{
	unsigned long flags;
	u32 val;
	unsigned int ret;

	spin_lock_irqsave(&port->lock, flags);

	val = owl_uart_read(port, OWL_UART_STAT);
	ret = (val & OWL_UART_STAT_TFES) ? TIOCSER_TEMT : 0;

	spin_unlock_irqrestore(&port->lock, flags);

	return ret;
}