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
struct tegra_vde {int /*<<< orphan*/ * domain; int /*<<< orphan*/  group; int /*<<< orphan*/  iova; int /*<<< orphan*/  iova_resv_static_addresses; int /*<<< orphan*/  iova_resv_last_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_detach_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_domain_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_group_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iova_cache_put () ; 
 int /*<<< orphan*/  put_iova_domain (int /*<<< orphan*/ *) ; 

void tegra_vde_iommu_deinit(struct tegra_vde *vde)
{
	if (vde->domain) {
		__free_iova(&vde->iova, vde->iova_resv_last_page);
		__free_iova(&vde->iova, vde->iova_resv_static_addresses);
		iommu_detach_group(vde->domain, vde->group);
		put_iova_domain(&vde->iova);
		iova_cache_put();
		iommu_domain_free(vde->domain);
		iommu_group_put(vde->group);

		vde->domain = NULL;
	}
}