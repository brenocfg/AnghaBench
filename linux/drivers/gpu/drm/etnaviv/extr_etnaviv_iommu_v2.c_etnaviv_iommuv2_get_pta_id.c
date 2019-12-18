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
struct etnaviv_iommuv2_context {unsigned short id; } ;
struct etnaviv_iommu_context {int dummy; } ;

/* Variables and functions */
 struct etnaviv_iommuv2_context* to_v2_context (struct etnaviv_iommu_context*) ; 

unsigned short etnaviv_iommuv2_get_pta_id(struct etnaviv_iommu_context *context)
{
	struct etnaviv_iommuv2_context *v2_context = to_v2_context(context);

	return v2_context->id;
}