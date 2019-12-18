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
struct ttm_placement {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;
struct drm_gem_vram_object {struct ttm_placement placement; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_SYSTEM ; 
 struct drm_gem_vram_object* drm_gem_vram_of_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  drm_gem_vram_placement (struct drm_gem_vram_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_is_gem_vram (struct ttm_buffer_object*) ; 

void drm_gem_vram_bo_driver_evict_flags(struct ttm_buffer_object *bo,
					struct ttm_placement *pl)
{
	struct drm_gem_vram_object *gbo;

	/* TTM may pass BOs that are not GEM VRAM BOs. */
	if (!drm_is_gem_vram(bo))
		return;

	gbo = drm_gem_vram_of_bo(bo);
	drm_gem_vram_placement(gbo, TTM_PL_FLAG_SYSTEM);
	*pl = gbo->placement;
}