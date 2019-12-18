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
struct ttm_placement {int dummy; } ;
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;
struct drm_vram_mm {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* evict_flags ) (struct ttm_buffer_object*,struct ttm_placement*) ;} ;

/* Variables and functions */
 struct drm_vram_mm* drm_vram_mm_of_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ttm_buffer_object*,struct ttm_placement*) ; 

__attribute__((used)) static void bo_driver_evict_flags(struct ttm_buffer_object *bo,
				  struct ttm_placement *placement)
{
	struct drm_vram_mm *vmm = drm_vram_mm_of_bdev(bo->bdev);

	if (vmm->funcs && vmm->funcs->evict_flags)
		vmm->funcs->evict_flags(bo, placement);
}