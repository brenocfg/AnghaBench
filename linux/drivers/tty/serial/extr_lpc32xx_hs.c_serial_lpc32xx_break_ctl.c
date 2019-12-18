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
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_HSUART_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_HSU_BREAK ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial_lpc32xx_break_ctl(struct uart_port *port,
				     int break_state)
{
	unsigned long flags;
	u32 tmp;

	spin_lock_irqsave(&port->lock, flags);
	tmp = readl(LPC32XX_HSUART_CTRL(port->membase));
	if (break_state != 0)
		tmp |= LPC32XX_HSU_BREAK;
	else
		tmp &= ~LPC32XX_HSU_BREAK;
	writel(tmp, LPC32XX_HSUART_CTRL(port->membase));
	spin_unlock_irqrestore(&port->lock, flags);
}