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
struct intel_iommu {size_t seq_id; int /*<<< orphan*/  domain_ids; int /*<<< orphan*/  lock; } ;
struct dmar_domain {scalar_t__* iommu_refcnt; int iommu_count; int* iommu_did; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_domain_lock ; 
 int /*<<< orphan*/  domain_update_iommu_cap (struct dmar_domain*) ; 
 int /*<<< orphan*/  set_iommu_domain (struct intel_iommu*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int domain_detach_iommu(struct dmar_domain *domain,
			       struct intel_iommu *iommu)
{
	int num, count;

	assert_spin_locked(&device_domain_lock);
	assert_spin_locked(&iommu->lock);

	domain->iommu_refcnt[iommu->seq_id] -= 1;
	count = --domain->iommu_count;
	if (domain->iommu_refcnt[iommu->seq_id] == 0) {
		num = domain->iommu_did[iommu->seq_id];
		clear_bit(num, iommu->domain_ids);
		set_iommu_domain(iommu, num, NULL);

		domain_update_iommu_cap(domain);
		domain->iommu_did[iommu->seq_id] = 0;
	}

	return count;
}