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
struct drm_gem_object {int dummy; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_mn_unregister (struct amdgpu_bo*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 

void amdgpu_gem_object_free(struct drm_gem_object *gobj)
{
	struct amdgpu_bo *robj = gem_to_amdgpu_bo(gobj);

	if (robj) {
		amdgpu_mn_unregister(robj);
		amdgpu_bo_unref(&robj);
	}
}