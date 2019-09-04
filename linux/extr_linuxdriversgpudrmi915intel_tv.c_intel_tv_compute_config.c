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
struct tv_mode {int /*<<< orphan*/  clock; } ;
struct intel_encoder {int dummy; } ;
struct drm_display_mode {int flags; int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int pipe_bpp; TYPE_1__ base; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 struct tv_mode* intel_tv_mode_find (struct drm_connector_state*) ; 

__attribute__((used)) static bool
intel_tv_compute_config(struct intel_encoder *encoder,
			struct intel_crtc_state *pipe_config,
			struct drm_connector_state *conn_state)
{
	const struct tv_mode *tv_mode = intel_tv_mode_find(conn_state);
	struct drm_display_mode *adjusted_mode =
		&pipe_config->base.adjusted_mode;

	if (!tv_mode)
		return false;

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return false;

	adjusted_mode->crtc_clock = tv_mode->clock;
	DRM_DEBUG_KMS("forcing bpc to 8 for TV\n");
	pipe_config->pipe_bpp = 8*3;

	/* TV has it's own notion of sync and other mode flags, so clear them. */
	adjusted_mode->flags = 0;

	/*
	 * FIXME: We don't check whether the input mode is actually what we want
	 * or whether userspace is doing something stupid.
	 */

	return true;
}