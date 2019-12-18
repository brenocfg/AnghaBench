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
struct sti_vtg {scalar_t__ regs; int /*<<< orphan*/  irq_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 scalar_t__ VTG_HOST_ITS ; 
 scalar_t__ VTG_HOST_ITS_BCLR ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t vtg_irq(int irq, void *arg)
{
	struct sti_vtg *vtg = arg;

	vtg->irq_status = readl(vtg->regs + VTG_HOST_ITS);

	writel(vtg->irq_status, vtg->regs + VTG_HOST_ITS_BCLR);

	/* force sync bus write */
	readl(vtg->regs + VTG_HOST_ITS);

	return IRQ_WAKE_THREAD;
}