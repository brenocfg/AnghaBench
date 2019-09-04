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
struct protection_domain {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_iommu_pd_list ; 
 int /*<<< orphan*/  amd_iommu_pd_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void add_domain_to_list(struct protection_domain *domain)
{
	unsigned long flags;

	spin_lock_irqsave(&amd_iommu_pd_lock, flags);
	list_add(&domain->list, &amd_iommu_pd_list);
	spin_unlock_irqrestore(&amd_iommu_pd_lock, flags);
}