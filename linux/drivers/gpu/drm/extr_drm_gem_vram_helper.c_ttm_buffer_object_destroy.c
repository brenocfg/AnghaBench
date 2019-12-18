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
struct ttm_buffer_object {int dummy; } ;
struct drm_gem_vram_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_vram_destroy (struct drm_gem_vram_object*) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_bo (struct ttm_buffer_object*) ; 

__attribute__((used)) static void ttm_buffer_object_destroy(struct ttm_buffer_object *bo)
{
	struct drm_gem_vram_object *gbo = drm_gem_vram_of_bo(bo);

	drm_gem_vram_destroy(gbo);
}