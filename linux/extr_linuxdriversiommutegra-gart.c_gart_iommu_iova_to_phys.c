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
struct iommu_domain {int dummy; } ;
struct gart_domain {struct gart_device* gart; } ;
struct gart_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  pte_lock; } ;
typedef  unsigned long phys_addr_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 unsigned long EINVAL ; 
 unsigned long GART_PAGE_MASK ; 
 int /*<<< orphan*/  __phys_to_pfn (unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long*) ; 
 int /*<<< orphan*/  gart_dump_table (struct gart_device*) ; 
 int /*<<< orphan*/  gart_iova_range_valid (struct gart_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long gart_read_pte (struct gart_device*,scalar_t__) ; 
 int /*<<< orphan*/  pfn_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct gart_domain* to_gart_domain (struct iommu_domain*) ; 

__attribute__((used)) static phys_addr_t gart_iommu_iova_to_phys(struct iommu_domain *domain,
					   dma_addr_t iova)
{
	struct gart_domain *gart_domain = to_gart_domain(domain);
	struct gart_device *gart = gart_domain->gart;
	unsigned long pte;
	phys_addr_t pa;
	unsigned long flags;

	if (!gart_iova_range_valid(gart, iova, 0))
		return -EINVAL;

	spin_lock_irqsave(&gart->pte_lock, flags);
	pte = gart_read_pte(gart, iova);
	spin_unlock_irqrestore(&gart->pte_lock, flags);

	pa = (pte & GART_PAGE_MASK);
	if (!pfn_valid(__phys_to_pfn(pa))) {
		dev_err(gart->dev, "No entry for %08llx:%pa\n",
			 (unsigned long long)iova, &pa);
		gart_dump_table(gart);
		return -EINVAL;
	}
	return pa;
}