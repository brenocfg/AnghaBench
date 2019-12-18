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
struct protection_domain {int /*<<< orphan*/  lock; int /*<<< orphan*/  mode; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_MODE_NONE ; 
 int /*<<< orphan*/  free_pagetable (struct protection_domain*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct protection_domain* to_pdomain (struct iommu_domain*) ; 
 int /*<<< orphan*/  update_domain (struct protection_domain*) ; 

void amd_iommu_domain_direct_map(struct iommu_domain *dom)
{
	struct protection_domain *domain = to_pdomain(dom);
	unsigned long flags;

	spin_lock_irqsave(&domain->lock, flags);

	/* Update data structure */
	domain->mode    = PAGE_MODE_NONE;

	/* Make changes visible to IOMMUs */
	update_domain(domain);

	/* Page-table is not visible to IOMMU anymore, so free it */
	free_pagetable(domain);

	spin_unlock_irqrestore(&domain->lock, flags);
}