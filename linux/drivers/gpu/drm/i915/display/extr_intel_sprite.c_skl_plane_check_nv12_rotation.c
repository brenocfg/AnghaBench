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
struct TYPE_3__ {unsigned int rotation; int /*<<< orphan*/  src; struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct drm_framebuffer {TYPE_2__* format; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_ROTATE_270 ; 
 unsigned int DRM_MODE_ROTATE_90 ; 
 int EINVAL ; 
 int drm_rect_width (int /*<<< orphan*/ *) ; 
 scalar_t__ is_planar_yuv_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_plane_check_nv12_rotation(const struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	unsigned int rotation = plane_state->base.rotation;
	int src_w = drm_rect_width(&plane_state->base.src) >> 16;

	/* Display WA #1106 */
	if (is_planar_yuv_format(fb->format->format) && src_w & 3 &&
	    (rotation == DRM_MODE_ROTATE_270 ||
	     rotation == (DRM_MODE_REFLECT_X | DRM_MODE_ROTATE_90))) {
		DRM_DEBUG_KMS("src width must be multiple of 4 for rotated planar YUV\n");
		return -EINVAL;
	}

	return 0;
}