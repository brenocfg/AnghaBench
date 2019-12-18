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
struct tegra_nand_controller {int /*<<< orphan*/  irq; int /*<<< orphan*/  dma_complete; int /*<<< orphan*/  command_complete; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ COMMAND ; 
 scalar_t__ DMA_MST_CTRL ; 
 scalar_t__ ISR ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tegra_nand_controller_abort(struct tegra_nand_controller *ctrl)
{
	u32 isr, dma;

	disable_irq(ctrl->irq);

	/* Abort current command/DMA operation */
	writel_relaxed(0, ctrl->regs + DMA_MST_CTRL);
	writel_relaxed(0, ctrl->regs + COMMAND);

	/* clear interrupts */
	isr = readl_relaxed(ctrl->regs + ISR);
	writel_relaxed(isr, ctrl->regs + ISR);
	dma = readl_relaxed(ctrl->regs + DMA_MST_CTRL);
	writel_relaxed(dma, ctrl->regs + DMA_MST_CTRL);

	reinit_completion(&ctrl->command_complete);
	reinit_completion(&ctrl->dma_complete);

	enable_irq(ctrl->irq);
}