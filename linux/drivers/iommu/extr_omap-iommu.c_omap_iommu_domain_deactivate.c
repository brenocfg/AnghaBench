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
struct omap_iommu_domain {int num_iommus; struct omap_iommu_device* iommus; int /*<<< orphan*/  dev; } ;
struct omap_iommu_device {struct omap_iommu* iommu_dev; } ;
struct omap_iommu {int /*<<< orphan*/  dev; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct omap_iommu_domain* to_omap_domain (struct iommu_domain*) ; 

int omap_iommu_domain_deactivate(struct iommu_domain *domain)
{
	struct omap_iommu_domain *omap_domain = to_omap_domain(domain);
	struct omap_iommu_device *iommu;
	struct omap_iommu *oiommu;
	int i;

	if (!omap_domain->dev)
		return 0;

	iommu = omap_domain->iommus;
	iommu += (omap_domain->num_iommus - 1);
	for (i = 0; i < omap_domain->num_iommus; i++, iommu--) {
		oiommu = iommu->iommu_dev;
		pm_runtime_put_sync(oiommu->dev);
	}

	return 0;
}