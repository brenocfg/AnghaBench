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
struct sysmmu_drvdata {int active; int /*<<< orphan*/  lock; scalar_t__ sfrbase; int /*<<< orphan*/  clk_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_DISABLE ; 
 scalar_t__ REG_MMU_CFG ; 
 scalar_t__ REG_MMU_CTRL ; 
 int /*<<< orphan*/  __sysmmu_disable_clocks (struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __sysmmu_disable(struct sysmmu_drvdata *data)
{
	unsigned long flags;

	clk_enable(data->clk_master);

	spin_lock_irqsave(&data->lock, flags);
	writel(CTRL_DISABLE, data->sfrbase + REG_MMU_CTRL);
	writel(0, data->sfrbase + REG_MMU_CFG);
	data->active = false;
	spin_unlock_irqrestore(&data->lock, flags);

	__sysmmu_disable_clocks(data);
}