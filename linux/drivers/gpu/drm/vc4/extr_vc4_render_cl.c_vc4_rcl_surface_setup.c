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
typedef  scalar_t__ uint8_t ;
struct vc4_exec_info {TYPE_1__* args; int /*<<< orphan*/  rcl_write_bo_count; struct drm_gem_cma_object** rcl_write_bo; } ;
struct drm_vc4_submit_rcl_surface {int bits; int flags; int offset; int /*<<< orphan*/  hindex; } ;
struct drm_gem_cma_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct drm_vc4_submit_rcl_surface zs_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int EINVAL ; 
 scalar_t__ VC4_GET_FIELD (int,int /*<<< orphan*/ ) ; 
#define  VC4_LOADSTORE_TILE_BUFFER_BGR565 130 
#define  VC4_LOADSTORE_TILE_BUFFER_BGR565_DITHER 129 
 int /*<<< orphan*/  VC4_LOADSTORE_TILE_BUFFER_BUFFER ; 
 int VC4_LOADSTORE_TILE_BUFFER_BUFFER_MASK ; 
 scalar_t__ VC4_LOADSTORE_TILE_BUFFER_COLOR ; 
 int /*<<< orphan*/  VC4_LOADSTORE_TILE_BUFFER_FORMAT ; 
 int VC4_LOADSTORE_TILE_BUFFER_FORMAT_MASK ; 
#define  VC4_LOADSTORE_TILE_BUFFER_RGBA8888 128 
 int /*<<< orphan*/  VC4_LOADSTORE_TILE_BUFFER_TILING ; 
 int VC4_LOADSTORE_TILE_BUFFER_TILING_MASK ; 
 scalar_t__ VC4_LOADSTORE_TILE_BUFFER_ZS ; 
 int VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES ; 
 scalar_t__ VC4_TILING_FORMAT_LT ; 
 int /*<<< orphan*/  vc4_check_tex_size (struct vc4_exec_info*,struct drm_gem_cma_object*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vc4_full_res_bounds_check (struct vc4_exec_info*,struct drm_gem_cma_object*,struct drm_vc4_submit_rcl_surface*) ; 
 struct drm_gem_cma_object* vc4_use_bo (struct vc4_exec_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc4_rcl_surface_setup(struct vc4_exec_info *exec,
				 struct drm_gem_cma_object **obj,
				 struct drm_vc4_submit_rcl_surface *surf,
				 bool is_write)
{
	uint8_t tiling = VC4_GET_FIELD(surf->bits,
				       VC4_LOADSTORE_TILE_BUFFER_TILING);
	uint8_t buffer = VC4_GET_FIELD(surf->bits,
				       VC4_LOADSTORE_TILE_BUFFER_BUFFER);
	uint8_t format = VC4_GET_FIELD(surf->bits,
				       VC4_LOADSTORE_TILE_BUFFER_FORMAT);
	int cpp;
	int ret;

	if (surf->flags & ~VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) {
		DRM_DEBUG("Extra flags set\n");
		return -EINVAL;
	}

	if (surf->hindex == ~0)
		return 0;

	*obj = vc4_use_bo(exec, surf->hindex);
	if (!*obj)
		return -EINVAL;

	if (is_write)
		exec->rcl_write_bo[exec->rcl_write_bo_count++] = *obj;

	if (surf->flags & VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) {
		if (surf == &exec->args->zs_write) {
			DRM_DEBUG("general zs write may not be a full-res.\n");
			return -EINVAL;
		}

		if (surf->bits != 0) {
			DRM_DEBUG("load/store general bits set with "
				  "full res load/store.\n");
			return -EINVAL;
		}

		ret = vc4_full_res_bounds_check(exec, *obj, surf);
		if (ret)
			return ret;

		return 0;
	}

	if (surf->bits & ~(VC4_LOADSTORE_TILE_BUFFER_TILING_MASK |
			   VC4_LOADSTORE_TILE_BUFFER_BUFFER_MASK |
			   VC4_LOADSTORE_TILE_BUFFER_FORMAT_MASK)) {
		DRM_DEBUG("Unknown bits in load/store: 0x%04x\n",
			  surf->bits);
		return -EINVAL;
	}

	if (tiling > VC4_TILING_FORMAT_LT) {
		DRM_DEBUG("Bad tiling format\n");
		return -EINVAL;
	}

	if (buffer == VC4_LOADSTORE_TILE_BUFFER_ZS) {
		if (format != 0) {
			DRM_DEBUG("No color format should be set for ZS\n");
			return -EINVAL;
		}
		cpp = 4;
	} else if (buffer == VC4_LOADSTORE_TILE_BUFFER_COLOR) {
		switch (format) {
		case VC4_LOADSTORE_TILE_BUFFER_BGR565:
		case VC4_LOADSTORE_TILE_BUFFER_BGR565_DITHER:
			cpp = 2;
			break;
		case VC4_LOADSTORE_TILE_BUFFER_RGBA8888:
			cpp = 4;
			break;
		default:
			DRM_DEBUG("Bad tile buffer format\n");
			return -EINVAL;
		}
	} else {
		DRM_DEBUG("Bad load/store buffer %d.\n", buffer);
		return -EINVAL;
	}

	if (surf->offset & 0xf) {
		DRM_DEBUG("load/store buffer must be 16b aligned.\n");
		return -EINVAL;
	}

	if (!vc4_check_tex_size(exec, *obj, surf->offset, tiling,
				exec->args->width, exec->args->height, cpp)) {
		return -EINVAL;
	}

	return 0;
}