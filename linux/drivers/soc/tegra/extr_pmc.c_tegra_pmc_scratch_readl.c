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
struct tegra_pmc {scalar_t__ scratch; scalar_t__ tz_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  tegra_pmc_readl (struct tegra_pmc*,unsigned long) ; 

__attribute__((used)) static u32 tegra_pmc_scratch_readl(struct tegra_pmc *pmc, unsigned long offset)
{
	if (pmc->tz_only)
		return tegra_pmc_readl(pmc, offset);

	return readl(pmc->scratch + offset);
}