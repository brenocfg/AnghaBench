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
struct gart_device {int /*<<< orphan*/  pte_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_GART_REGS (struct gart_device*) ; 
 int /*<<< orphan*/  gart_iova_range_valid (struct gart_device*,unsigned long,size_t) ; 
 int /*<<< orphan*/  gart_set_pte (struct gart_device*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct gart_domain* to_gart_domain (struct iommu_domain*) ; 

__attribute__((used)) static size_t gart_iommu_unmap(struct iommu_domain *domain, unsigned long iova,
			       size_t bytes)
{
	struct gart_domain *gart_domain = to_gart_domain(domain);
	struct gart_device *gart = gart_domain->gart;
	unsigned long flags;

	if (!gart_iova_range_valid(gart, iova, bytes))
		return 0;

	spin_lock_irqsave(&gart->pte_lock, flags);
	gart_set_pte(gart, iova, 0);
	FLUSH_GART_REGS(gart);
	spin_unlock_irqrestore(&gart->pte_lock, flags);
	return bytes;
}