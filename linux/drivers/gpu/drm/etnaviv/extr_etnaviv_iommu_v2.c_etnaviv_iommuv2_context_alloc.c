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
typedef  int u64 ;
struct etnaviv_iommu_context {int /*<<< orphan*/  mm; int /*<<< orphan*/  mappings; int /*<<< orphan*/  lock; int /*<<< orphan*/  refcount; struct etnaviv_iommu_global* global; } ;
struct etnaviv_iommuv2_context {size_t id; struct etnaviv_iommu_context base; int /*<<< orphan*/  mtlb_dma; int /*<<< orphan*/  mtlb_cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  pta_alloc; int /*<<< orphan*/ * pta_cpu; } ;
struct etnaviv_iommu_global {TYPE_1__ v2; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t ETNAVIV_PTA_ENTRIES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMUv2_MAX_STLB_ENTRIES ; 
 int /*<<< orphan*/  MMUv2_PTE_EXCEPTION ; 
 scalar_t__ SZ_1G ; 
 scalar_t__ SZ_4K ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 size_t find_first_zero_bit (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct etnaviv_iommuv2_context*) ; 
 struct etnaviv_iommuv2_context* vzalloc (int) ; 

struct etnaviv_iommu_context *
etnaviv_iommuv2_context_alloc(struct etnaviv_iommu_global *global)
{
	struct etnaviv_iommuv2_context *v2_context;
	struct etnaviv_iommu_context *context;

	v2_context = vzalloc(sizeof(*v2_context));
	if (!v2_context)
		return NULL;

	mutex_lock(&global->lock);
	v2_context->id = find_first_zero_bit(global->v2.pta_alloc,
					     ETNAVIV_PTA_ENTRIES);
	if (v2_context->id < ETNAVIV_PTA_ENTRIES) {
		set_bit(v2_context->id, global->v2.pta_alloc);
	} else {
		mutex_unlock(&global->lock);
		goto out_free;
	}
	mutex_unlock(&global->lock);

	v2_context->mtlb_cpu = dma_alloc_wc(global->dev, SZ_4K,
					    &v2_context->mtlb_dma, GFP_KERNEL);
	if (!v2_context->mtlb_cpu)
		goto out_free_id;

	memset32(v2_context->mtlb_cpu, MMUv2_PTE_EXCEPTION,
		 MMUv2_MAX_STLB_ENTRIES);

	global->v2.pta_cpu[v2_context->id] = v2_context->mtlb_dma;

	context = &v2_context->base;
	context->global = global;
	kref_init(&context->refcount);
	mutex_init(&context->lock);
	INIT_LIST_HEAD(&context->mappings);
	drm_mm_init(&context->mm, SZ_4K, (u64)SZ_1G * 4 - SZ_4K);

	return context;

out_free_id:
	clear_bit(v2_context->id, global->v2.pta_alloc);
out_free:
	vfree(v2_context);
	return NULL;
}