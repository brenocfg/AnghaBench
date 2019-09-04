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
struct ttm_place {unsigned long fpfn; unsigned long lpfn; } ;
struct TYPE_3__ {unsigned long num_pages; int mem_type; struct drm_mm_node* mm_node; } ;
struct ttm_buffer_object {TYPE_1__ mem; int /*<<< orphan*/  resv; } ;
struct reservation_object_list {int shared_count; int /*<<< orphan*/ * shared; } ;
struct drm_mm_node {unsigned long start; unsigned long size; } ;
struct dma_fence {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 
 scalar_t__ amdkfd_fence_check_mm (struct dma_fence*,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct reservation_object_list* reservation_object_get_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reservation_object_held (int /*<<< orphan*/ ) ; 
 int ttm_bo_eviction_valuable (struct ttm_buffer_object*,struct ttm_place const*) ; 

__attribute__((used)) static bool amdgpu_ttm_bo_eviction_valuable(struct ttm_buffer_object *bo,
					    const struct ttm_place *place)
{
	unsigned long num_pages = bo->mem.num_pages;
	struct drm_mm_node *node = bo->mem.mm_node;
	struct reservation_object_list *flist;
	struct dma_fence *f;
	int i;

	/* If bo is a KFD BO, check if the bo belongs to the current process.
	 * If true, then return false as any KFD process needs all its BOs to
	 * be resident to run successfully
	 */
	flist = reservation_object_get_list(bo->resv);
	if (flist) {
		for (i = 0; i < flist->shared_count; ++i) {
			f = rcu_dereference_protected(flist->shared[i],
				reservation_object_held(bo->resv));
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