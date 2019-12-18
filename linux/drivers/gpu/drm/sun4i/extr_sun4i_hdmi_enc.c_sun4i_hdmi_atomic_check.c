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
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int flags; } ;
struct drm_crtc_state {struct drm_display_mode mode; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLCLK ; 
 int EINVAL ; 

__attribute__((used)) static int sun4i_hdmi_atomic_check(struct drm_encoder *encoder,
				   struct drm_crtc_state *crtc_state,
				   struct drm_connector_state *conn_state)
{
	struct drm_display_mode *mode = &crtc_state->mode;

	if (mode->flags & DRM_MODE_FLAG_DBLCLK)
		return -EINVAL;

	return 0;
}