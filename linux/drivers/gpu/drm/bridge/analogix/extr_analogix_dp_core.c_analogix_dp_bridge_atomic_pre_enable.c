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
struct drm_crtc_state {scalar_t__ self_refresh_active; } ;
struct drm_crtc {int dummy; } ;
struct drm_bridge {struct analogix_dp_device* driver_private; } ;
struct drm_atomic_state {int dummy; } ;
struct analogix_dp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 struct drm_crtc* analogix_dp_get_new_crtc (struct analogix_dp_device*,struct drm_atomic_state*) ; 
 int analogix_dp_prepare_panel (struct analogix_dp_device*,int,int) ; 
 struct drm_crtc_state* drm_atomic_get_old_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 

__attribute__((used)) static void analogix_dp_bridge_atomic_pre_enable(struct drm_bridge *bridge,
						 struct drm_atomic_state *state)
{
	struct analogix_dp_device *dp = bridge->driver_private;
	struct drm_crtc *crtc;
	struct drm_crtc_state *old_crtc_state;
	int ret;

	crtc = analogix_dp_get_new_crtc(dp, state);
	if (!crtc)
		return;

	old_crtc_state = drm_atomic_get_old_crtc_state(state, crtc);
	/* Don't touch the panel if we're coming back from PSR */
	if (old_crtc_state && old_crtc_state->self_refresh_active)
		return;

	ret = analogix_dp_prepare_panel(dp, true, true);
	if (ret)
		DRM_ERROR("failed to setup the panel ret = %d\n", ret);
}