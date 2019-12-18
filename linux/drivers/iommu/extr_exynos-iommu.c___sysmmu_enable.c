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
struct sysmmu_drvdata {int active; int /*<<< orphan*/  clk_master; int /*<<< orphan*/  lock; scalar_t__ sfrbase; int /*<<< orphan*/  pgtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_BLOCK ; 
 int /*<<< orphan*/  CTRL_ENABLE ; 
 scalar_t__ REG_MMU_CTRL ; 
 int /*<<< orphan*/  __sysmmu_enable_clocks (struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  __sysmmu_init_config (struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  __sysmmu_set_ptbase (struct sysmmu_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __sysmmu_enable(struct sysmmu_drvdata *data)
{
	unsigned long flags;

	__sysmmu_enable_clocks(data);

	spin_lock_irqsave(&data->lock, flags);
	writel(CTRL_BLOCK, data->sfrbase + REG_MMU_CTRL);
	__sysmmu_init_config(data);
	__sysmmu_set_ptbase(data, data->pgtable);
	writel(CTRL_ENABLE, data->sfrbase + REG_MMU_CTRL);
	data->active = true;
	spin_unlock_irqrestore(&data->lock, flags);

	/*
	 * SYSMMU driver keeps master's clock enabled only for the short
	 * time, while accessing the registers. For performing address
	 * translation during DMA transaction it relies on the client
	 * driver to enable it.
	 */
	clk_disable(data->clk_master);
}