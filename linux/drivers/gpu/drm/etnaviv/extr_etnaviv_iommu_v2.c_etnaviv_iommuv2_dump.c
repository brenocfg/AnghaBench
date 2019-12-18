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
struct etnaviv_iommuv2_context {int* mtlb_cpu; int** stlb_cpu; } ;
struct etnaviv_iommu_context {int dummy; } ;

/* Variables and functions */
 int MMUv2_MAX_STLB_ENTRIES ; 
 int MMUv2_PTE_PRESENT ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  memcpy (void*,int*,int /*<<< orphan*/ ) ; 
 struct etnaviv_iommuv2_context* to_v2_context (struct etnaviv_iommu_context*) ; 

__attribute__((used)) static void etnaviv_iommuv2_dump(struct etnaviv_iommu_context *context, void *buf)
{
	struct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	int i;

	memcpy(buf, v2_context->mtlb_cpu, SZ_4K);
	buf += SZ_4K;
	for (i = 0; i < MMUv2_MAX_STLB_ENTRIES; i++)
		if (v2_context->mtlb_cpu[i] & MMUv2_PTE_PRESENT) {
			memcpy(buf, v2_context->stlb_cpu[i], SZ_4K);
			buf += SZ_4K;
		}
}