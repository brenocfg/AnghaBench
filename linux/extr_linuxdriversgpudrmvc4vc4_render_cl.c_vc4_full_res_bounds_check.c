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
typedef  int u32 ;
struct vc4_exec_info {struct drm_vc4_submit_cl* args; } ;
struct drm_vc4_submit_rcl_surface {scalar_t__ offset; } ;
struct drm_vc4_submit_cl {int max_y_tile; int max_x_tile; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {scalar_t__ size; } ;
struct drm_gem_cma_object {TYPE_1__ base; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int,...) ; 
 int EINVAL ; 
 int VC4_TILE_BUFFER_SIZE ; 

__attribute__((used)) static int vc4_full_res_bounds_check(struct vc4_exec_info *exec,
				     struct drm_gem_cma_object *obj,
				     struct drm_vc4_submit_rcl_surface *surf)
{
	struct drm_vc4_submit_cl *args = exec->args;
	u32 render_tiles_stride = DIV_ROUND_UP(exec->args->width, 32);

	if (surf->offset > obj->base.size) {
		DRM_DEBUG("surface offset %d > BO size %zd\n",
			  surf->offset, obj->base.size);
		return -EINVAL;
	}

	if ((obj->base.size - surf->offset) / VC4_TILE_BUFFER_SIZE <
	    render_tiles_stride * args->max_y_tile + args->max_x_tile) {
		DRM_DEBUG("MSAA tile %d, %d out of bounds "
			  "(bo size %zd, offset %d).\n",
			  args->max_x_tile, args->max_y_tile,
			  obj->base.size,
			  surf->offset);
		return -EINVAL;
	}

	return 0;
}