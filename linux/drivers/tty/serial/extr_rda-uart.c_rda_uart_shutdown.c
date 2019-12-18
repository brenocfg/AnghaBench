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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDA_UART_CTRL ; 
 int /*<<< orphan*/  RDA_UART_ENABLE ; 
 int /*<<< orphan*/  rda_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rda_uart_stop_rx (struct uart_port*) ; 
 int /*<<< orphan*/  rda_uart_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  rda_uart_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rda_uart_shutdown(struct uart_port *port)
{
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);

	rda_uart_stop_tx(port);
	rda_uart_stop_rx(port);

	val = rda_uart_read(port, RDA_UART_CTRL);
	val &= ~RDA_UART_ENABLE;
	rda_uart_write(port, val, RDA_UART_CTRL);

	spin_unlock_irqrestore(&port->lock, flags);
}