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
struct etnaviv_gpu {TYPE_1__* mmu; } ;
struct TYPE_2__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ETNAVIV_IOMMU_V1 ; 
 int /*<<< orphan*/  etnaviv_iommuv1_restore (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_iommuv2_restore (struct etnaviv_gpu*) ; 

void etnaviv_iommu_restore(struct etnaviv_gpu *gpu)
{
	if (gpu->mmu->version == ETNAVIV_IOMMU_V1)
		etnaviv_iommuv1_restore(gpu);
	else
		etnaviv_iommuv2_restore(gpu);
}