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
struct analogix_dp_device {scalar_t__ dpms_mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ DRM_MODE_DPMS_ON ; 
 int MAX_PLL_LOCK_LOOP ; 
 int analogix_dp_disable_psr (struct analogix_dp_device*) ; 
 struct drm_crtc* analogix_dp_get_new_crtc (struct analogix_dp_device*,struct drm_atomic_state*) ; 
 scalar_t__ analogix_dp_set_bridge (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct drm_crtc_state* drm_atomic_get_old_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void analogix_dp_bridge_atomic_enable(struct drm_bridge *bridge,
					     struct drm_atomic_state *state)
{
	struct analogix_dp_device *dp = bridge->driver_private;
	struct drm_crtc *crtc;
	struct drm_crtc_state *old_crtc_state;
	int timeout_loop = 0;
	int ret;

	crtc = analogix_dp_get_new_crtc(dp, state);
	if (!crtc)
		return;

	old_crtc_state = drm_atomic_get_old_crtc_state(state, crtc);
	/* Not a full enable, just disable PSR and continue */
	if (old_crtc_state && old_crtc_state->self_refresh_active) {
		ret = analogix_dp_disable_psr(dp);
		if (ret)
			DRM_ERROR("Failed to disable psr %d\n", ret);
		return;
	}

	if (dp->dpms_mode == DRM_MODE_DPMS_ON)
		return;

	while (timeout_loop < MAX_PLL_LOCK_LOOP) {
		if (analogix_dp_set_bridge(dp) == 0) {
			dp->dpms_mode = DRM_MODE_DPMS_ON;
			return;
		}
		dev_err(dp->dev, "failed to set bridge, retry: %d\n",
			timeout_loop);
		timeout_loop++;
		usleep_range(10, 11);
	}
	dev_err(dp->dev, "too many times retry set bridge, give it up\n");
}