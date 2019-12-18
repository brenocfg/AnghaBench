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
typedef  int /*<<< orphan*/  u32 ;
struct etnaviv_iommuv2_context {int /*<<< orphan*/  mtlb_dma; } ;
struct etnaviv_iommu_context {int dummy; } ;

/* Variables and functions */
 struct etnaviv_iommuv2_context* to_v2_context (struct etnaviv_iommu_context*) ; 

u32 etnaviv_iommuv2_get_mtlb_addr(struct etnaviv_iommu_context *context)
{
	struct etnaviv_iommuv2_context *v2_context = to_v2_context(context);

	return v2_context->mtlb_dma;
}