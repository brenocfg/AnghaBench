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
struct mcde {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MCDE_IMSCCHNL ; 
 scalar_t__ MCDE_IMSCOVL ; 
 scalar_t__ MCDE_IMSCPP ; 
 scalar_t__ MCDE_RISCHNL ; 
 scalar_t__ MCDE_RISOVL ; 
 scalar_t__ MCDE_RISPP ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void mcde_display_disable_irqs(struct mcde *mcde)
{
	/* Disable all IRQs */
	writel(0, mcde->regs + MCDE_IMSCPP);
	writel(0, mcde->regs + MCDE_IMSCOVL);
	writel(0, mcde->regs + MCDE_IMSCCHNL);

	/* Clear any pending IRQs */
	writel(0xFFFFFFFF, mcde->regs + MCDE_RISPP);
	writel(0xFFFFFFFF, mcde->regs + MCDE_RISOVL);
	writel(0xFFFFFFFF, mcde->regs + MCDE_RISCHNL);
}