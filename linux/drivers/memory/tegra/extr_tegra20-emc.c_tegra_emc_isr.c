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
struct tegra_emc {scalar_t__ regs; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_handshake_complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EMC_CLKCHANGE_COMPLETE_INT ; 
 scalar_t__ EMC_INTSTATUS ; 
 int EMC_REFRESH_OVERFLOW_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t tegra_emc_isr(int irq, void *data)
{
	struct tegra_emc *emc = data;
	u32 intmask = EMC_REFRESH_OVERFLOW_INT | EMC_CLKCHANGE_COMPLETE_INT;
	u32 status;

	status = readl_relaxed(emc->regs + EMC_INTSTATUS) & intmask;
	if (!status)
		return IRQ_NONE;

	/* notify about EMC-CAR handshake completion */
	if (status & EMC_CLKCHANGE_COMPLETE_INT)
		complete(&emc->clk_handshake_complete);

	/* notify about HW problem */
	if (status & EMC_REFRESH_OVERFLOW_INT)
		dev_err_ratelimited(emc->dev,
				    "refresh request overflow timeout\n");

	/* clear interrupts */
	writel_relaxed(status, emc->regs + EMC_INTSTATUS);

	return IRQ_HANDLED;
}