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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_HSUART_CTRL (int /*<<< orphan*/ ) ; 
 int LPC32XX_HSU_OFFSET (int) ; 
 int LPC32XX_HSU_RX_TL32B ; 
 int LPC32XX_HSU_TMO_INACT_4B ; 
 int LPC32XX_HSU_TX_TL8B ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  lpc32xx_loopback_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial_lpc32xx_shutdown(struct uart_port *port)
{
	u32 tmp;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	tmp = LPC32XX_HSU_TX_TL8B | LPC32XX_HSU_RX_TL32B |
		LPC32XX_HSU_OFFSET(20) | LPC32XX_HSU_TMO_INACT_4B;
	writel(tmp, LPC32XX_HSUART_CTRL(port->membase));

	lpc32xx_loopback_set(port->mapbase, 1); /* go to loopback mode */

	spin_unlock_irqrestore(&port->lock, flags);

	free_irq(port->irq, port);
}