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
struct tegra_dpaux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAUX_HYBRID_SPARE ; 
 int /*<<< orphan*/  DPAUX_HYBRID_SPARE_PAD_POWER_DOWN ; 
 int /*<<< orphan*/  tegra_dpaux_readl (struct tegra_dpaux*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dpaux_writel (struct tegra_dpaux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dpaux_pad_power_up(struct tegra_dpaux *dpaux)
{
	u32 value = tegra_dpaux_readl(dpaux, DPAUX_HYBRID_SPARE);

	value &= ~DPAUX_HYBRID_SPARE_PAD_POWER_DOWN;

	tegra_dpaux_writel(dpaux, value, DPAUX_HYBRID_SPARE);
}