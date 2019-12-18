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
typedef  size_t uint32_t ;
struct vc4_exec_info {size_t bo_count; struct drm_gem_cma_object** bo; } ;
struct vc4_bo {scalar_t__ validated_shader; } ;
struct drm_gem_cma_object {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 struct vc4_bo* to_vc4_bo (int /*<<< orphan*/ *) ; 

struct drm_gem_cma_object *
vc4_use_bo(struct vc4_exec_info *exec, uint32_t hindex)
{
	struct drm_gem_cma_object *obj;
	struct vc4_bo *bo;

	if (hindex >= exec->bo_count) {
		DRM_DEBUG("BO index %d greater than BO count %d\n",
			  hindex, exec->bo_count);
		return NULL;
	}
	obj = exec->bo[hindex];
	bo = to_vc4_bo(&obj->base);

	if (bo->validated_shader) {
		DRM_DEBUG("Trying to use shader BO as something other than "
			  "a shader\n");
		return NULL;
	}

	return obj;
}