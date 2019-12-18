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
struct TYPE_2__ {int /*<<< orphan*/  visible; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {int /*<<< orphan*/  ctl; TYPE_1__ base; } ;
struct intel_plane {int dummy; } ;
struct intel_crtc_state {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int chv_plane_check_rotation (struct intel_plane_state*) ; 
 int drm_atomic_helper_check_plane_state (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i9xx_check_plane_surface (struct intel_plane_state*) ; 
 int /*<<< orphan*/  i9xx_plane_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int /*<<< orphan*/  i9xx_plane_has_windowing (struct intel_plane*) ; 
 int intel_plane_check_src_coordinates (struct intel_plane_state*) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i9xx_plane_check(struct intel_crtc_state *crtc_state,
		 struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	int ret;

	ret = chv_plane_check_rotation(plane_state);
	if (ret)
		return ret;

	ret = drm_atomic_helper_check_plane_state(&plane_state->base,
						  &crtc_state->base,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  i9xx_plane_has_windowing(plane),
						  true);
	if (ret)
		return ret;

	ret = i9xx_check_plane_surface(plane_state);
	if (ret)
		return ret;

	if (!plane_state->base.visible)
		return 0;

	ret = intel_plane_check_src_coordinates(plane_state);
	if (ret)
		return ret;

	plane_state->ctl = i9xx_plane_ctl(crtc_state, plane_state);

	return 0;
}