#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_pmc {int /*<<< orphan*/  powergates_lock; TYPE_1__* soc; } ;
struct TYPE_2__ {scalar_t__ has_gpu_clamps; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPU_RG_CNTRL ; 
 int /*<<< orphan*/  REMOVE_CLAMPING ; 
 unsigned int TEGRA_POWERGATE_3D ; 
 int TEGRA_POWERGATE_PCIE ; 
 unsigned int TEGRA_POWERGATE_VDEC ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_pmc_writel (struct tegra_pmc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __tegra_powergate_remove_clamping(struct tegra_pmc *pmc,
					     unsigned int id)
{
	u32 mask;

	mutex_lock(&pmc->powergates_lock);

	/*
	 * On Tegra124 and later, the clamps for the GPU are controlled by a
	 * separate register (with different semantics).
	 */
	if (id == TEGRA_POWERGATE_3D) {
		if (pmc->soc->has_gpu_clamps) {
			tegra_pmc_writel(pmc, 0, GPU_RG_CNTRL);
			goto out;
		}
	}

	/*
	 * Tegra 2 has a bug where PCIE and VDE clamping masks are
	 * swapped relatively to the partition ids
	 */
	if (id == TEGRA_POWERGATE_VDEC)
		mask = (1 << TEGRA_POWERGATE_PCIE);
	else if (id == TEGRA_POWERGATE_PCIE)
		mask = (1 << TEGRA_POWERGATE_VDEC);
	else
		mask = (1 << id);

	tegra_pmc_writel(pmc, mask, REMOVE_CLAMPING);

out:
	mutex_unlock(&pmc->powergates_lock);

	return 0;
}