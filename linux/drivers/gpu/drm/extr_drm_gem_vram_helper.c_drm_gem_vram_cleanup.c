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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct drm_gem_vram_object {TYPE_1__ bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_gem_vram_cleanup(struct drm_gem_vram_object *gbo)
{
	/* We got here via ttm_bo_put(), which means that the
	 * TTM buffer object in 'bo' has already been cleaned
	 * up; only release the GEM object.
	 */
	drm_gem_object_release(&gbo->bo.base);
}