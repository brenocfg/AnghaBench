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
struct etnaviv_iommuv1_context {int /*<<< orphan*/  pgtable_cpu; } ;
struct etnaviv_iommu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct etnaviv_iommuv1_context* to_v1_context (struct etnaviv_iommu_context*) ; 

__attribute__((used)) static void etnaviv_iommuv1_dump(struct etnaviv_iommu_context *context,
				 void *buf)
{
	struct etnaviv_iommuv1_context *v1_context = to_v1_context(context);

	memcpy(buf, v1_context->pgtable_cpu, PT_SIZE);
}