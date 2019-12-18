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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct imx_port {int context_saved; int* saved_reg; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX21_UTS ; 
 int /*<<< orphan*/  UBIR ; 
 int /*<<< orphan*/  UBMR ; 
 int /*<<< orphan*/  UCR1 ; 
 int /*<<< orphan*/  UCR2 ; 
 int UCR2_SRST ; 
 int /*<<< orphan*/  UCR3 ; 
 int /*<<< orphan*/  UCR4 ; 
 int /*<<< orphan*/  UESC ; 
 int /*<<< orphan*/  UFCR ; 
 int /*<<< orphan*/  UTIM ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void imx_uart_restore_context(struct imx_port *sport)
{
	unsigned long flags;

	spin_lock_irqsave(&sport->port.lock, flags);
	if (!sport->context_saved) {
		spin_unlock_irqrestore(&sport->port.lock, flags);
		return;
	}

	imx_uart_writel(sport, sport->saved_reg[4], UFCR);
	imx_uart_writel(sport, sport->saved_reg[5], UESC);
	imx_uart_writel(sport, sport->saved_reg[6], UTIM);
	imx_uart_writel(sport, sport->saved_reg[7], UBIR);
	imx_uart_writel(sport, sport->saved_reg[8], UBMR);
	imx_uart_writel(sport, sport->saved_reg[9], IMX21_UTS);
	imx_uart_writel(sport, sport->saved_reg[0], UCR1);
	imx_uart_writel(sport, sport->saved_reg[1] | UCR2_SRST, UCR2);
	imx_uart_writel(sport, sport->saved_reg[2], UCR3);
	imx_uart_writel(sport, sport->saved_reg[3], UCR4);
	sport->context_saved = false;
	spin_unlock_irqrestore(&sport->port.lock, flags);
}