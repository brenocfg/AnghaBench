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
typedef  int /*<<< orphan*/  u64 ;
struct protection_domain {int /*<<< orphan*/  lock; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int __amd_iommu_flush_page (struct protection_domain*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct protection_domain* to_pdomain (struct iommu_domain*) ; 

int amd_iommu_flush_page(struct iommu_domain *dom, int pasid,
			 u64 address)
{
	struct protection_domain *domain = to_pdomain(dom);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&domain->lock, flags);
	ret = __amd_iommu_flush_page(domain, pasid, address);
	spin_unlock_irqrestore(&domain->lock, flags);

	return ret;
}