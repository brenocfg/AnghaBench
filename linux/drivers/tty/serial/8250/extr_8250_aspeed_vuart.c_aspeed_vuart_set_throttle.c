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
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aspeed_vuart_set_throttle (struct uart_8250_port*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void aspeed_vuart_set_throttle(struct uart_port *port, bool throttle)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	__aspeed_vuart_set_throttle(up, throttle);
	spin_unlock_irqrestore(&port->lock, flags);
}