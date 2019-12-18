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
struct imx_port {int context_saved; TYPE_1__ port; void** saved_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX21_UTS ; 
 int /*<<< orphan*/  UBIR ; 
 int /*<<< orphan*/  UBMR ; 
 int /*<<< orphan*/  UCR1 ; 
 int /*<<< orphan*/  UCR2 ; 
 int /*<<< orphan*/  UCR3 ; 
 int /*<<< orphan*/  UCR4 ; 
 int /*<<< orphan*/  UESC ; 
 int /*<<< orphan*/  UFCR ; 
 int /*<<< orphan*/  UTIM ; 
 void* imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void imx_uart_save_context(struct imx_port *sport)
{
	unsigned long flags;

	/* Save necessary regs */
	spin_lock_irqsave(&sport->port.lock, flags);
	sport->saved_reg[0] = imx_uart_readl(sport, UCR1);
	sport->saved_reg[1] = imx_uart_readl(sport, UCR2);
	sport->saved_reg[2] = imx_uart_readl(sport, UCR3);
	sport->saved_reg[3] = imx_uart_readl(sport, UCR4);
	sport->saved_reg[4] = imx_uart_readl(sport, UFCR);
	sport->saved_reg[5] = imx_uart_readl(sport, UESC);
	sport->saved_reg[6] = imx_uart_readl(sport, UTIM);
	sport->saved_reg[7] = imx_uart_readl(sport, UBIR);
	sport->saved_reg[8] = imx_uart_readl(sport, UBMR);
	sport->saved_reg[9] = imx_uart_readl(sport, IMX21_UTS);
	sport->context_saved = true;
	spin_unlock_irqrestore(&sport->port.lock, flags);
}