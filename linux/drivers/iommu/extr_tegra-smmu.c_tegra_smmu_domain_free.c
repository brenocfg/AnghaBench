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
struct tegra_smmu_as {struct tegra_smmu_as* pts; struct tegra_smmu_as* count; int /*<<< orphan*/  use_count; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tegra_smmu_as*) ; 
 struct tegra_smmu_as* to_smmu_as (struct iommu_domain*) ; 

__attribute__((used)) static void tegra_smmu_domain_free(struct iommu_domain *domain)
{
	struct tegra_smmu_as *as = to_smmu_as(domain);

	/* TODO: free page directory and page tables */

	WARN_ON_ONCE(as->use_count);
	kfree(as->count);
	kfree(as->pts);
	kfree(as);
}