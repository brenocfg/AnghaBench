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
struct vc4_rcl_setup {int dummy; } ;
struct vc4_exec_info {TYPE_1__* args; int /*<<< orphan*/  rcl_write_bo_count; struct drm_gem_cma_object** rcl_write_bo; } ;
struct drm_vc4_submit_rcl_surface {int bits; scalar_t__ flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  hindex; } ;
struct drm_gem_cma_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int EINVAL ; 
 scalar_t__ VC4_GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int VC4_RENDER_CONFIG_DECIMATE_MODE_4X ; 
 int /*<<< orphan*/  VC4_RENDER_CONFIG_FORMAT ; 
#define  VC4_RENDER_CONFIG_FORMAT_BGR565 130 
#define  VC4_RENDER_CONFIG_FORMAT_BGR565_DITHERED 129 
 int VC4_RENDER_CONFIG_FORMAT_MASK ; 
#define  VC4_RENDER_CONFIG_FORMAT_RGBA8888 128 
 int /*<<< orphan*/  VC4_RENDER_CONFIG_MEMORY_FORMAT ; 
 int VC4_RENDER_CONFIG_MEMORY_FORMAT_MASK ; 
 int VC4_RENDER_CONFIG_MS_MODE_4X ; 
 scalar_t__ VC4_TILING_FORMAT_LT ; 
 int /*<<< orphan*/  vc4_check_tex_size (struct vc4_exec_info*,struct drm_gem_cma_object*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct drm_gem_cma_object* vc4_use_bo (struct vc4_exec_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vc4_rcl_render_config_surface_setup(struct vc4_exec_info *exec,
				    struct vc4_rcl_setup *setup,
				    struct drm_gem_cma_object **obj,
				    struct drm_vc4_submit_rcl_surface *surf)
{
	uint8_t tiling = VC4_GET_FIELD(surf->bits,
				       VC4_RENDER_CONFIG_MEMORY_FORMAT);
	uint8_t format = VC4_GET_FIELD(surf->bits,
				       VC4_RENDER_CONFIG_FORMAT);
	int cpp;

	if (surf->flags != 0) {
		DRM_DEBUG("No flags supported on render config.\n");
		return -EINVAL;
	}

	if (surf->bits & ~(VC4_RENDER_CONFIG_MEMORY_FORMAT_MASK |
			   VC4_RENDER_CONFIG_FORMAT_MASK |
			   VC4_RENDER_CONFIG_MS_MODE_4X |
			   VC4_RENDER_CONFIG_DECIMATE_MODE_4X)) {
		DRM_DEBUG("Unknown bits in render config: 0x%04x\n",
			  surf->bits);
		return -EINVAL;
	}

	if (surf->hindex == ~0)
		return 0;

	*obj = vc4_use_bo(exec, surf->hindex);
	if (!*obj)
		return -EINVAL;

	exec->rcl_write_bo[exec->rcl_write_bo_count++] = *obj;

	if (tiling > VC4_TILING_FORMAT_LT) {
		DRM_DEBUG("Bad tiling format\n");
		return -EINVAL;
	}

	switch (format) {
	case VC4_RENDER_CONFIG_FORMAT_BGR565_DITHERED:
	case VC4_RENDER_CONFIG_FORMAT_BGR565:
		cpp = 2;
		break;
	case VC4_RENDER_CONFIG_FORMAT_RGBA8888:
		cpp = 4;
		break;
	default:
		DRM_DEBUG("Bad tile buffer format\n");
		return -EINVAL;
	}

	if (!vc4_check_tex_size(exec, *obj, surf->offset, tiling,
				exec->args->width, exec->args->height, cpp)) {
		return -EINVAL;
	}

	return 0;
}