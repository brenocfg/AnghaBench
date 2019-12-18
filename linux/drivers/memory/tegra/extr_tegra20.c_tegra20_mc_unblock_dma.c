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
struct tegra_mc_reset {int /*<<< orphan*/  control; int /*<<< orphan*/  bit; } ;
struct tegra_mc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int mc_readl (struct tegra_mc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_writel (struct tegra_mc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int tegra20_mc_unblock_dma(struct tegra_mc *mc,
				  const struct tegra_mc_reset *rst)
{
	unsigned long flags;
	u32 value;

	spin_lock_irqsave(&mc->lock, flags);

	value = mc_readl(mc, rst->control) | BIT(rst->bit);
	mc_writel(mc, value, rst->control);

	spin_unlock_irqrestore(&mc->lock, flags);

	return 0;
}