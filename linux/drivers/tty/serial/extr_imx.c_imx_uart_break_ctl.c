#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct imx_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCR1 ; 
 int UCR1_SNDBRK ; 
 int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void imx_uart_break_ctl(struct uart_port *port, int break_state)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned long flags;
	u32 ucr1;

	spin_lock_irqsave(&sport->port.lock, flags);

	ucr1 = imx_uart_readl(sport, UCR1) & ~UCR1_SNDBRK;

	if (break_state != 0)
		ucr1 |= UCR1_SNDBRK;

	imx_uart_writel(sport, ucr1, UCR1);

	spin_unlock_irqrestore(&sport->port.lock, flags);
}