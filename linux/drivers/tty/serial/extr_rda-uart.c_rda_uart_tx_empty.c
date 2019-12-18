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
 int /*<<< orphan*/  RDA_UART_STATUS ; 
 int RDA_UART_TX_FIFO_MASK ; 
 unsigned int TIOCSER_TEMT ; 
 int rda_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int rda_uart_tx_empty(struct uart_port *port)
{
	unsigned long flags;
	unsigned int ret;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);

	val = rda_uart_read(port, RDA_UART_STATUS);
	ret = (val & RDA_UART_TX_FIFO_MASK) ? TIOCSER_TEMT : 0;

	spin_unlock_irqrestore(&port->lock, flags);

	return ret;
}