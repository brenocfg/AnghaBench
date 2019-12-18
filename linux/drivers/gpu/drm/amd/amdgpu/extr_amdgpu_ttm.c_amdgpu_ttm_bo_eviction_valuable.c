#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ttm_place {unsigned long fpfn; unsigned long lpfn; } ;
struct TYPE_5__ {unsigned long num_pages; int mem_type; struct drm_mm_node* mm_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {scalar_t__ type; TYPE_2__ mem; TYPE_1__ base; } ;
struct drm_mm_node {unsigned long start; unsigned long size; } ;
struct dma_resv_list {int shared_count; int /*<<< orphan*/ * shared; } ;
struct dma_fence {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 
 scalar_t__ amdkfd_fence_check_mm (struct dma_fence*,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 struct dma_resv_list* dma_resv_get_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_resv_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_resv_test_signaled_rcu (int /*<<< orphan*/ ,int) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_bo_eviction_valuable (struct ttm_buffer_object*,struct ttm_place const*) ; 
 scalar_t__ ttm_bo_type_kernel ; 

__attribute__((used)) static bool amdgpu_ttm_bo_eviction_valuable(struct ttm_buffer_object *bo,
					    const struct ttm_place *place)
{
	unsigned long num_pages = bo->mem.num_pages;
	struct drm_mm_node *node = bo->mem.mm_node;
	struct dma_resv_list *flist;
	struct dma_fence *f;
	int i;

	/* Don't evict VM page tables while they are busy, otherwise we can't
	 * cleanly handle page faults.
	 */
	if (bo->type == ttm_bo_type_kernel &&
	    !dma_resv_test_signaled_rcu(bo->base.resv, true))
		return false;

	/* If bo is a KFD BO, check if the bo belongs to the current process.
	 * If true, then return false as any KFD process needs all its BOs to
	 * be resident to run successfully
	 */
	flist = dma_resv_get_list(bo->base.resv);
	if (flist) {
		for (i = 0; i < flist->shared_count; ++i) {
			f = rcu_dereference_protected(flist->shared[i],
				dma_resv_held(bo->base.resv));
			if (amdkfd_fence_check_mm(f, current->mm))
				return false;
		}
	}

	switch (bo->mem.mem_type) {
	case TTM_PL_TT:
		return true;

	case TTM_PL_VRAM:
		/* Check each drm MM node individually */
		while (num_pages) {
			if (place->fpfn < (node->start + node->size) &&
			    !(place->lpfn && place->lpfn <= node->start))
				return true;

			num_pages -= node->size;
			++node;
		}
		return false;

	default:
		break;
	}

	return ttm_bo_eviction_valuable(bo, place);
}