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
struct protection_domain {int /*<<< orphan*/  lock; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int __set_gcr3 (struct protection_domain*,int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct protection_domain* to_pdomain (struct iommu_domain*) ; 

int amd_iommu_domain_set_gcr3(struct iommu_domain *dom, int pasid,
			      unsigned long cr3)
{
	struct protection_domain *domain = to_pdomain(dom);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&domain->lock, flags);
	ret = __set_gcr3(domain, pasid, cr3);
	spin_unlock_irqrestore(&domain->lock, flags);

	return ret;
}