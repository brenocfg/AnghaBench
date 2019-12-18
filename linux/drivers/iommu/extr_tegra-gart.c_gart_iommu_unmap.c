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
struct iommu_iotlb_gather {int dummy; } ;
struct iommu_domain {int dummy; } ;
struct gart_device {int /*<<< orphan*/  pte_lock; } ;

/* Variables and functions */
 int __gart_iommu_unmap (struct gart_device*,unsigned long) ; 
 struct gart_device* gart_handle ; 
 scalar_t__ gart_iova_range_invalid (struct gart_device*,unsigned long,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t gart_iommu_unmap(struct iommu_domain *domain, unsigned long iova,
			       size_t bytes, struct iommu_iotlb_gather *gather)
{
	struct gart_device *gart = gart_handle;
	int err;

	if (gart_iova_range_invalid(gart, iova, bytes))
		return 0;

	spin_lock(&gart->pte_lock);
	err = __gart_iommu_unmap(gart, iova);
	spin_unlock(&gart->pte_lock);

	return err ? 0 : bytes;
}