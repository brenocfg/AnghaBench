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
typedef  scalar_t__ u32 ;
struct mcde {scalar_t__ regs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MCDE_MISERR ; 
 scalar_t__ MCDE_RISERR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mcde_display_irq (struct mcde*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mcde_irq(int irq, void *data)
{
	struct mcde *mcde = data;
	u32 val;

	val = readl(mcde->regs + MCDE_MISERR);

	mcde_display_irq(mcde);

	if (val)
		dev_info(mcde->dev, "some error IRQ\n");
	writel(val, mcde->regs + MCDE_RISERR);

	return IRQ_HANDLED;
}