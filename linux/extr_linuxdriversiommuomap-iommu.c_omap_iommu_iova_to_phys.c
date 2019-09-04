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
struct omap_iommu_domain {struct omap_iommu_device* iommus; } ;
struct omap_iommu_device {struct omap_iommu* iommu_dev; } ;
struct omap_iommu {struct device* dev; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOLARGE_MASK ; 
 int /*<<< orphan*/  IOPTE_MASK ; 
 int /*<<< orphan*/  IOSECTION_MASK ; 
 int /*<<< orphan*/  IOSUPER_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ iopgd_is_section (int /*<<< orphan*/ ) ; 
 scalar_t__ iopgd_is_super (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iopgtable_lookup_entry (struct omap_iommu*,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ iopte_is_large (int /*<<< orphan*/ ) ; 
 scalar_t__ iopte_is_small (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_iommu_translate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct omap_iommu_domain* to_omap_domain (struct iommu_domain*) ; 

__attribute__((used)) static phys_addr_t omap_iommu_iova_to_phys(struct iommu_domain *domain,
					   dma_addr_t da)
{
	struct omap_iommu_domain *omap_domain = to_omap_domain(domain);
	struct omap_iommu_device *iommu = omap_domain->iommus;
	struct omap_iommu *oiommu = iommu->iommu_dev;
	struct device *dev = oiommu->dev;
	u32 *pgd, *pte;
	phys_addr_t ret = 0;

	/*
	 * all the iommus within the domain will have identical programming,
	 * so perform the lookup using just the first iommu
	 */
	iopgtable_lookup_entry(oiommu, da, &pgd, &pte);

	if (pte) {
		if (iopte_is_small(*pte))
			ret = omap_iommu_translate(*pte, da, IOPTE_MASK);
		else if (iopte_is_large(*pte))
			ret = omap_iommu_translate(*pte, da, IOLARGE_MASK);
		else
			dev_err(dev, "bogus pte 0x%x, da 0x%llx", *pte,
				(unsigned long long)da);
	} else {
		if (iopgd_is_section(*pgd))
			ret = omap_iommu_translate(*pgd, da, IOSECTION_MASK);
		else if (iopgd_is_super(*pgd))
			ret = omap_iommu_translate(*pgd, da, IOSUPER_MASK);
		else
			dev_err(dev, "bogus pgd 0x%x, da 0x%llx", *pgd,
				(unsigned long long)da);
	}

	return ret;
}