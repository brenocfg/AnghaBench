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
struct ttm_place {unsigned long fpfn; unsigned long lpfn; int flags; } ;
struct ttm_mem_type_manager {struct amdgpu_gtt_mgr* priv; int /*<<< orphan*/  bdev; } ;
struct ttm_mem_reg {int /*<<< orphan*/  start; int /*<<< orphan*/  page_alignment; int /*<<< orphan*/  num_pages; struct amdgpu_gtt_node* mm_node; } ;
struct ttm_buffer_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct amdgpu_gtt_node {TYPE_2__ node; } ;
struct amdgpu_gtt_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;
struct TYPE_3__ {unsigned long num_cpu_pages; } ;
struct amdgpu_device {TYPE_1__ gart; } ;
typedef  enum drm_mm_insert_mode { ____Placeholder_drm_mm_insert_mode } drm_mm_insert_mode ;

/* Variables and functions */
 int DRM_MM_INSERT_BEST ; 
 int DRM_MM_INSERT_HIGH ; 
 int TTM_PL_FLAG_TOPDOWN ; 
 scalar_t__ amdgpu_gtt_mgr_has_gart_addr (struct ttm_mem_reg*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int drm_mm_insert_node_in_range (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_gtt_mgr_alloc(struct ttm_mem_type_manager *man,
				struct ttm_buffer_object *tbo,
				const struct ttm_place *place,
				struct ttm_mem_reg *mem)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(man->bdev);
	struct amdgpu_gtt_mgr *mgr = man->priv;
	struct amdgpu_gtt_node *node = mem->mm_node;
	enum drm_mm_insert_mode mode;
	unsigned long fpfn, lpfn;
	int r;

	if (amdgpu_gtt_mgr_has_gart_addr(mem))
		return 0;

	if (place)
		fpfn = place->fpfn;
	else
		fpfn = 0;

	if (place && place->lpfn)
		lpfn = place->lpfn;
	else
		lpfn = adev->gart.num_cpu_pages;

	mode = DRM_MM_INSERT_BEST;
	if (place && place->flags & TTM_PL_FLAG_TOPDOWN)
		mode = DRM_MM_INSERT_HIGH;

	spin_lock(&mgr->lock);
	r = drm_mm_insert_node_in_range(&mgr->mm, &node->node, mem->num_pages,
					mem->page_alignment, 0, fpfn, lpfn,
					mode);
	spin_unlock(&mgr->lock);

	if (!r)
		mem->start = node->node.start;

	return r;
}