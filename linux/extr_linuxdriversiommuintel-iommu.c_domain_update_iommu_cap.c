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
struct dmar_domain {int /*<<< orphan*/  iommu_superpage; int /*<<< orphan*/  iommu_snooping; } ;

/* Variables and functions */
 int /*<<< orphan*/  domain_update_iommu_coherency (struct dmar_domain*) ; 
 int /*<<< orphan*/  domain_update_iommu_snooping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  domain_update_iommu_superpage (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void domain_update_iommu_cap(struct dmar_domain *domain)
{
	domain_update_iommu_coherency(domain);
	domain->iommu_snooping = domain_update_iommu_snooping(NULL);
	domain->iommu_superpage = domain_update_iommu_superpage(NULL);
}