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
typedef  int /*<<< orphan*/  sysmmu_pte_t ;
struct iommu_domain {int dummy; } ;
struct exynos_iommu_domain {int /*<<< orphan*/  pgtablelock; int /*<<< orphan*/  pgtable; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ lpage_offs (int /*<<< orphan*/ ) ; 
 scalar_t__ lpage_phys (int /*<<< orphan*/ *) ; 
 scalar_t__ lv1ent_page (int /*<<< orphan*/ *) ; 
 scalar_t__ lv1ent_section (int /*<<< orphan*/ *) ; 
 scalar_t__ lv2ent_large (int /*<<< orphan*/ *) ; 
 scalar_t__ lv2ent_small (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * page_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * section_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ section_offs (int /*<<< orphan*/ ) ; 
 scalar_t__ section_phys (int /*<<< orphan*/ *) ; 
 scalar_t__ spage_offs (int /*<<< orphan*/ ) ; 
 scalar_t__ spage_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct exynos_iommu_domain* to_exynos_domain (struct iommu_domain*) ; 

__attribute__((used)) static phys_addr_t exynos_iommu_iova_to_phys(struct iommu_domain *iommu_domain,
					  dma_addr_t iova)
{
	struct exynos_iommu_domain *domain = to_exynos_domain(iommu_domain);
	sysmmu_pte_t *entry;
	unsigned long flags;
	phys_addr_t phys = 0;

	spin_lock_irqsave(&domain->pgtablelock, flags);

	entry = section_entry(domain->pgtable, iova);

	if (lv1ent_section(entry)) {
		phys = section_phys(entry) + section_offs(iova);
	} else if (lv1ent_page(entry)) {
		entry = page_entry(entry, iova);

		if (lv2ent_large(entry))
			phys = lpage_phys(entry) + lpage_offs(iova);
		else if (lv2ent_small(entry))
			phys = spage_phys(entry) + spage_offs(iova);
	}

	spin_unlock_irqrestore(&domain->pgtablelock, flags);

	return phys;
}