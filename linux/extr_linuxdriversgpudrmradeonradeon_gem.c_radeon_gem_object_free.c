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
struct radeon_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  radeon_bo_unref (struct radeon_bo**) ; 
 int /*<<< orphan*/  radeon_mn_unregister (struct radeon_bo*) ; 

void radeon_gem_object_free(struct drm_gem_object *gobj)
{
	struct radeon_bo *robj = gem_to_radeon_bo(gobj);

	if (robj) {
		radeon_mn_unregister(robj);
		radeon_bo_unref(&robj);
	}
}