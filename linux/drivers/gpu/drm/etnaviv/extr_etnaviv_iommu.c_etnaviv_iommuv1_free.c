#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct etnaviv_iommuv1_context {int /*<<< orphan*/  pgtable_dma; int /*<<< orphan*/  pgtable_cpu; } ;
struct etnaviv_iommu_context {TYPE_2__* global; int /*<<< orphan*/  mm; } ;
struct TYPE_3__ {int /*<<< orphan*/ * shared_context; } ;
struct TYPE_4__ {TYPE_1__ v1; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_SIZE ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_iommuv1_context*) ; 
 struct etnaviv_iommuv1_context* to_v1_context (struct etnaviv_iommu_context*) ; 

__attribute__((used)) static void etnaviv_iommuv1_free(struct etnaviv_iommu_context *context)
{
	struct etnaviv_iommuv1_context *v1_context = to_v1_context(context);

	drm_mm_takedown(&context->mm);

	dma_free_wc(context->global->dev, PT_SIZE, v1_context->pgtable_cpu,
		    v1_context->pgtable_dma);

	context->global->v1.shared_context = NULL;

	kfree(v1_context);
}