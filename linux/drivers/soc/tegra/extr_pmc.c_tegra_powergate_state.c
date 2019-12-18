#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* soc; } ;
struct TYPE_4__ {scalar_t__ has_gpu_clamps; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  GPU_RG_CNTRL ; 
 int /*<<< orphan*/  PWRGATE_STATUS ; 
 int TEGRA_POWERGATE_3D ; 
 TYPE_2__* pmc ; 
 int tegra_pmc_readl (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool tegra_powergate_state(int id)
{
	if (id == TEGRA_POWERGATE_3D && pmc->soc->has_gpu_clamps)
		return (tegra_pmc_readl(pmc, GPU_RG_CNTRL) & 0x1) == 0;
	else
		return (tegra_pmc_readl(pmc, PWRGATE_STATUS) & BIT(id)) != 0;
}