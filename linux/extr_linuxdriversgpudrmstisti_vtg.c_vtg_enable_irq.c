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
struct sti_vtg {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ VTG_HOST_ITM_BCLR ; 
 scalar_t__ VTG_HOST_ITM_BSET ; 
 scalar_t__ VTG_HOST_ITS_BCLR ; 
 int VTG_IRQ_MASK ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void vtg_enable_irq(struct sti_vtg *vtg)
{
	/* clear interrupt status and mask */
	writel(0xFFFF, vtg->regs + VTG_HOST_ITS_BCLR);
	writel(0xFFFF, vtg->regs + VTG_HOST_ITM_BCLR);
	writel(VTG_IRQ_MASK, vtg->regs + VTG_HOST_ITM_BSET);
}