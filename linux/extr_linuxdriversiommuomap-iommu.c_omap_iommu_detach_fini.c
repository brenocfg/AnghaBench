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
struct omap_iommu_domain {int num_iommus; struct omap_iommu_device* iommus; } ;
struct omap_iommu_device {struct omap_iommu_device* pgtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct omap_iommu_device*) ; 

__attribute__((used)) static void omap_iommu_detach_fini(struct omap_iommu_domain *odomain)
{
	int i;
	struct omap_iommu_device *iommu = odomain->iommus;

	for (i = 0; iommu && i < odomain->num_iommus; i++, iommu++)
		kfree(iommu->pgtable);

	kfree(odomain->iommus);
	odomain->num_iommus = 0;
	odomain->iommus = NULL;
}