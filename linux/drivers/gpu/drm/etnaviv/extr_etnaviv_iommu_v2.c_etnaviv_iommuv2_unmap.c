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
struct etnaviv_iommuv2_context {int /*<<< orphan*/ ** stlb_cpu; } ;
struct etnaviv_iommu_context {int dummy; } ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long MMUv2_MTLB_MASK ; 
 unsigned long MMUv2_MTLB_SHIFT ; 
 int /*<<< orphan*/  MMUv2_PTE_EXCEPTION ; 
 unsigned long MMUv2_STLB_MASK ; 
 unsigned long MMUv2_STLB_SHIFT ; 
 size_t SZ_4K ; 
 struct etnaviv_iommuv2_context* to_v2_context (struct etnaviv_iommu_context*) ; 

__attribute__((used)) static size_t etnaviv_iommuv2_unmap(struct etnaviv_iommu_context *context,
				    unsigned long iova, size_t size)
{
	struct etnaviv_iommuv2_context *etnaviv_domain = to_v2_context(context);
	int mtlb_entry, stlb_entry;

	if (size != SZ_4K)
		return -EINVAL;

	mtlb_entry = (iova & MMUv2_MTLB_MASK) >> MMUv2_MTLB_SHIFT;
	stlb_entry = (iova & MMUv2_STLB_MASK) >> MMUv2_STLB_SHIFT;

	etnaviv_domain->stlb_cpu[mtlb_entry][stlb_entry] = MMUv2_PTE_EXCEPTION;

	return SZ_4K;
}