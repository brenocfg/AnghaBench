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
typedef  scalar_t__ u64 ;
struct ttm_mem_reg {unsigned int num_pages; scalar_t__ start; struct drm_mm_node* mm_node; } ;
struct drm_mm_node {scalar_t__ size; } ;
struct TYPE_4__ {scalar_t__ visible_vram_size; } ;
struct amdgpu_device {TYPE_2__ gmc; } ;
struct TYPE_3__ {struct ttm_mem_reg mem; int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {TYPE_1__ tbo; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ amdgpu_bo_size (struct amdgpu_bo*) ; 
 scalar_t__ amdgpu_gmc_vram_full_visible (TYPE_2__*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_vram_mgr_vis_size (struct amdgpu_device*,struct drm_mm_node*) ; 

u64 amdgpu_vram_mgr_bo_visible_size(struct amdgpu_bo *bo)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	struct ttm_mem_reg *mem = &bo->tbo.mem;
	struct drm_mm_node *nodes = mem->mm_node;
	unsigned pages = mem->num_pages;
	u64 usage;

	if (amdgpu_gmc_vram_full_visible(&adev->gmc))
		return amdgpu_bo_size(bo);

	if (mem->start >= adev->gmc.visible_vram_size >> PAGE_SHIFT)
		return 0;

	for (usage = 0; nodes && pages; pages -= nodes->size, nodes++)
		usage += amdgpu_vram_mgr_vis_size(adev, nodes);

	return usage;
}