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
struct pic32_sport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_UART_STA ; 
 int /*<<< orphan*/  PIC32_UART_STA_UTXBRK ; 
 int /*<<< orphan*/  pic32_uart_writel (struct pic32_sport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pic32_sport* to_pic32_sport (struct uart_port*) ; 

__attribute__((used)) static void pic32_uart_break_ctl(struct uart_port *port, int ctl)
{
	struct pic32_sport *sport = to_pic32_sport(port);
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	if (ctl)
		pic32_uart_writel(sport, PIC32_SET(PIC32_UART_STA),
					PIC32_UART_STA_UTXBRK);
	else
		pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_STA),
					PIC32_UART_STA_UTXBRK);

	spin_unlock_irqrestore(&port->lock, flags);
}