#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct etnaviv_iommuv1_context {int /*<<< orphan*/ * pgtable_cpu; } ;
struct etnaviv_iommu_context {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/  bad_page_dma; } ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long GPU_MEM_START ; 
 unsigned long SZ_4K ; 
 struct etnaviv_iommuv1_context* to_v1_context (struct etnaviv_iommu_context*) ; 

__attribute__((used)) static size_t etnaviv_iommuv1_unmap(struct etnaviv_iommu_context *context,
	unsigned long iova, size_t size)
{
	struct etnaviv_iommuv1_context *v1_context = to_v1_context(context);
	unsigned int index = (iova - GPU_MEM_START) / SZ_4K;

	if (size != SZ_4K)
		return -EINVAL;

	v1_context->pgtable_cpu[index] = context->global->bad_page_dma;

	return SZ_4K;
}