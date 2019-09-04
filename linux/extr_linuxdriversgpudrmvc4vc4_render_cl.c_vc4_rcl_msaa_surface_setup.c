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
struct vc4_exec_info {int /*<<< orphan*/  rcl_write_bo_count; struct drm_gem_cma_object** rcl_write_bo; } ;
struct drm_vc4_submit_rcl_surface {scalar_t__ flags; scalar_t__ bits; int offset; int /*<<< orphan*/  hindex; } ;
struct drm_gem_cma_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int vc4_full_res_bounds_check (struct vc4_exec_info*,struct drm_gem_cma_object*,struct drm_vc4_submit_rcl_surface*) ; 
 struct drm_gem_cma_object* vc4_use_bo (struct vc4_exec_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc4_rcl_msaa_surface_setup(struct vc4_exec_info *exec,
				      struct drm_gem_cma_object **obj,
				      struct drm_vc4_submit_rcl_surface *surf)
{
	if (surf->flags != 0 || surf->bits != 0) {
		DRM_DEBUG("MSAA surface had nonzero flags/bits\n");
		return -EINVAL;
	}

	if (surf->hindex == ~0)
		return 0;

	*obj = vc4_use_bo(exec, surf->hindex);
	if (!*obj)
		return -EINVAL;

	exec->rcl_write_bo[exec->rcl_write_bo_count++] = *obj;

	if (surf->offset & 0xf) {
		DRM_DEBUG("MSAA write must be 16b aligned.\n");
		return -EINVAL;
	}

	return vc4_full_res_bounds_check(exec, *obj, surf);
}