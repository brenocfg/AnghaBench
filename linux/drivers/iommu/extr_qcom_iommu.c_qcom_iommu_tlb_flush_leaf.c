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

/* Variables and functions */
 int /*<<< orphan*/  qcom_iommu_tlb_inv_range_nosync (unsigned long,size_t,size_t,int,void*) ; 
 int /*<<< orphan*/  qcom_iommu_tlb_sync (void*) ; 

__attribute__((used)) static void qcom_iommu_tlb_flush_leaf(unsigned long iova, size_t size,
				      size_t granule, void *cookie)
{
	qcom_iommu_tlb_inv_range_nosync(iova, size, granule, true, cookie);
	qcom_iommu_tlb_sync(cookie);
}