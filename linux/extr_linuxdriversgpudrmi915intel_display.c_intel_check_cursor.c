#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int src_x; int src_y; struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_1__ main; TYPE_2__ base; } ;
struct intel_crtc_state {int /*<<< orphan*/  base; } ;
struct drm_framebuffer {scalar_t__ modifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 int drm_atomic_helper_check_plane_state (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  intel_add_fb_offsets (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_compute_tile_offset (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_check_cursor(struct intel_crtc_state *crtc_state,
			      struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	int src_x, src_y;
	u32 offset;
	int ret;

	ret = drm_atomic_helper_check_plane_state(&plane_state->base,
						  &crtc_state->base,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	if (ret)
		return ret;

	if (!fb)
		return 0;

	if (fb->modifier != DRM_FORMAT_MOD_LINEAR) {
		DRM_DEBUG_KMS("cursor cannot be tiled\n");
		return -EINVAL;
	}

	src_x = plane_state->base.src_x >> 16;
	src_y = plane_state->base.src_y >> 16;

	intel_add_fb_offsets(&src_x, &src_y, plane_state, 0);
	offset = intel_compute_tile_offset(&src_x, &src_y, plane_state, 0);

	if (src_x != 0 || src_y != 0) {
		DRM_DEBUG_KMS("Arbitrary cursor panning not supported\n");
		return -EINVAL;
	}

	plane_state->main.offset = offset;

	return 0;
}