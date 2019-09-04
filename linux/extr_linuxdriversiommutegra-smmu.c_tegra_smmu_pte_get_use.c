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
struct tegra_smmu_as {int /*<<< orphan*/ * count; } ;

/* Variables and functions */
 unsigned int iova_pd_index (unsigned long) ; 

__attribute__((used)) static void tegra_smmu_pte_get_use(struct tegra_smmu_as *as, unsigned long iova)
{
	unsigned int pd_index = iova_pd_index(iova);

	as->count[pd_index]++;
}