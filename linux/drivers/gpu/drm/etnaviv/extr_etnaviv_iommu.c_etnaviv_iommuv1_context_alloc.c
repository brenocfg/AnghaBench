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
struct etnaviv_iommu_context {struct etnaviv_iommu_global* global; int /*<<< orphan*/  mm; int /*<<< orphan*/  mappings; int /*<<< orphan*/  lock; int /*<<< orphan*/  refcount; } ;
struct etnaviv_iommuv1_context {struct etnaviv_iommu_context base; int /*<<< orphan*/  pgtable_cpu; int /*<<< orphan*/  pgtable_dma; } ;
struct TYPE_2__ {struct etnaviv_iommu_context* shared_context; } ;
struct etnaviv_iommu_global {int /*<<< orphan*/  lock; TYPE_1__ v1; int /*<<< orphan*/  bad_page_dma; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPU_MEM_START ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PT_ENTRIES ; 
 int /*<<< orphan*/  PT_SIZE ; 
 int SZ_4K ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  etnaviv_iommu_context_get (struct etnaviv_iommu_context*) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_iommuv1_context*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct etnaviv_iommuv1_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct etnaviv_iommu_context *
etnaviv_iommuv1_context_alloc(struct etnaviv_iommu_global *global)
{
	struct etnaviv_iommuv1_context *v1_context;
	struct etnaviv_iommu_context *context;

	mutex_lock(&global->lock);

	/*
	 * MMUv1 does not support switching between different contexts without
	 * a stop the world operation, so we only support a single shared
	 * context with this version.
	 */
	if (global->v1.shared_context) {
		context = global->v1.shared_context;
		etnaviv_iommu_context_get(context);
		mutex_unlock(&global->lock);
		return context;
	}

	v1_context = kzalloc(sizeof(*v1_context), GFP_KERNEL);
	if (!v1_context) {
		mutex_unlock(&global->lock);
		return NULL;
	}

	v1_context->pgtable_cpu = dma_alloc_wc(global->dev, PT_SIZE,
					       &v1_context->pgtable_dma,
					       GFP_KERNEL);
	if (!v1_context->pgtable_cpu)
		goto out_free;

	memset32(v1_context->pgtable_cpu, global->bad_page_dma, PT_ENTRIES);

	context = &v1_context->base;
	context->global = global;
	kref_init(&context->refcount);
	mutex_init(&context->lock);
	INIT_LIST_HEAD(&context->mappings);
	drm_mm_init(&context->mm, GPU_MEM_START, PT_ENTRIES * SZ_4K);
	context->global->v1.shared_context = context;

	mutex_unlock(&global->lock);

	return context;

out_free:
	mutex_unlock(&global->lock);
	kfree(v1_context);
	return NULL;
}