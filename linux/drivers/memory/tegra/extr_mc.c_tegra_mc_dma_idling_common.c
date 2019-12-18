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
struct tegra_mc_reset {int /*<<< orphan*/  bit; int /*<<< orphan*/  status; } ;
struct tegra_mc {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int mc_readl (struct tegra_mc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tegra_mc_dma_idling_common(struct tegra_mc *mc,
				       const struct tegra_mc_reset *rst)
{
	return (mc_readl(mc, rst->status) & BIT(rst->bit)) != 0;
}