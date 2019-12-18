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
struct intel_iommu {size_t seq_id; int /*<<< orphan*/  node; int /*<<< orphan*/  domain_ids; int /*<<< orphan*/  name; int /*<<< orphan*/  cap; int /*<<< orphan*/  lock; } ;
struct dmar_domain {int* iommu_refcnt; int iommu_count; int* iommu_did; int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 unsigned long cap_ndoms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_domain_lock ; 
 int /*<<< orphan*/  domain_update_iommu_cap (struct dmar_domain*) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_iommu_domain (struct intel_iommu*,int,struct dmar_domain*) ; 

__attribute__((used)) static int domain_attach_iommu(struct dmar_domain *domain,
			       struct intel_iommu *iommu)
{
	unsigned long ndomains;
	int num;

	assert_spin_locked(&device_domain_lock);
	assert_spin_locked(&iommu->lock);

	domain->iommu_refcnt[iommu->seq_id] += 1;
	domain->iommu_count += 1;
	if (domain->iommu_refcnt[iommu->seq_id] == 1) {
		ndomains = cap_ndoms(iommu->cap);
		num      = find_first_zero_bit(iommu->domain_ids, ndomains);

		if (num >= ndomains) {
			pr_err("%s: No free domain ids\n", iommu->name);
			domain->iommu_refcnt[iommu->seq_id] -= 1;
			domain->iommu_count -= 1;
			return -ENOSPC;
		}

		set_bit(num, iommu->domain_ids);
		set_iommu_domain(iommu, num, domain);

		domain->iommu_did[iommu->seq_id] = num;
		domain->nid			 = iommu->node;

		domain_update_iommu_cap(domain);
	}

	return 0;
}