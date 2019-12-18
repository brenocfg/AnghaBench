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
struct rp2_uart_port {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  RP2_CHAN_STAT ; 
 struct rp2_uart_port* port_to_up (struct uart_port*) ; 
 int /*<<< orphan*/  rp2_mask_ch_irq (struct rp2_uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp2_rmw (struct rp2_uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp2_uart_break_ctl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rp2_uart_shutdown(struct uart_port *port)
{
	struct rp2_uart_port *up = port_to_up(port);
	unsigned long flags;

	rp2_uart_break_ctl(port, 0);

	spin_lock_irqsave(&port->lock, flags);
	rp2_mask_ch_irq(up, up->idx, 0);
	rp2_rmw(up, RP2_CHAN_STAT, 0, 0);
	spin_unlock_irqrestore(&port->lock, flags);
}