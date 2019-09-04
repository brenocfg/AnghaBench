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
struct TYPE_2__ {int rotation; int /*<<< orphan*/  src; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int DRM_MODE_REFLECT_X ; 
 int DRM_MODE_ROTATE_270 ; 
 int DRM_MODE_ROTATE_90 ; 
 int EINVAL ; 
 int drm_rect_height (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
skl_check_nv12_surface(const struct intel_crtc_state *crtc_state,
		       struct intel_plane_state *plane_state)
{
	/* Display WA #1106 */
	if (plane_state->base.rotation !=
	    (DRM_MODE_REFLECT_X | DRM_MODE_ROTATE_90) &&
	    plane_state->base.rotation != DRM_MODE_ROTATE_270)
		return 0;

	/*
	 * src coordinates are rotated here.
	 * We check height but report it as width
	 */
	if (((drm_rect_height(&plane_state->base.src) >> 16) % 4) != 0) {
		DRM_DEBUG_KMS("src width must be multiple "
			      "of 4 for rotated NV12\n");
		return -EINVAL;
	}

	return 0;
}