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

/* Variables and functions */
 int /*<<< orphan*/  mtk_iommu_tlb_add_flush_nosync (unsigned long,size_t,size_t,int,void*) ; 

__attribute__((used)) static void mtk_iommu_tlb_flush_page_nosync(struct iommu_iotlb_gather *gather,
					    unsigned long iova, size_t granule,
					    void *cookie)
{
	mtk_iommu_tlb_add_flush_nosync(iova, granule, granule, true, cookie);
}