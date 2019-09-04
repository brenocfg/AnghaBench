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
struct gart_device {int /*<<< orphan*/  pte_lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLUSH_GART_REGS (struct gart_device*) ; 
 unsigned long GART_ENTRY_PHYS_ADDR_VALID ; 
 int /*<<< orphan*/  GART_PTE (unsigned long) ; 
 unsigned long __phys_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ gart_debug ; 
 int /*<<< orphan*/  gart_iova_range_valid (struct gart_device*,unsigned long,size_t) ; 
 unsigned long gart_read_pte (struct gart_device*,unsigned long) ; 
 int /*<<< orphan*/  gart_set_pte (struct gart_device*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct gart_domain* to_gart_domain (struct iommu_domain*) ; 

__attribute__((used)) static int gart_iommu_map(struct iommu_domain *domain, unsigned long iova,
			  phys_addr_t pa, size_t bytes, int prot)
{
	struct gart_domain *gart_domain = to_gart_domain(domain);
	struct gart_device *gart = gart_domain->gart;
	unsigned long flags;
	unsigned long pfn;
	unsigned long pte;

	if (!gart_iova_range_valid(gart, iova, bytes))
		return -EINVAL;

	spin_lock_irqsave(&gart->pte_lock, flags);
	pfn = __phys_to_pfn(pa);
	if (!pfn_valid(pfn)) {
		dev_err(gart->dev, "Invalid page: %pa\n", &pa);
		spin_unlock_irqrestore(&gart->pte_lock, flags);
		return -EINVAL;
	}
	if (gart_debug) {
		pte = gart_read_pte(gart, iova);
		if (pte & GART_ENTRY_PHYS_ADDR_VALID) {
			spin_unlock_irqrestore(&gart->pte_lock, flags);
			dev_err(gart->dev, "Page entry is in-use\n");
			return -EBUSY;
		}
	}
	gart_set_pte(gart, iova, GART_PTE(pfn));
	FLUSH_GART_REGS(gart);
	spin_unlock_irqrestore(&gart->pte_lock, flags);
	return 0;
}