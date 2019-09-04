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
struct intel_encoder {int dummy; } ;
struct drm_display_mode {int flags; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int has_pch_encoder; TYPE_1__ base; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 

__attribute__((used)) static bool pch_crt_compute_config(struct intel_encoder *encoder,
				   struct intel_crtc_state *pipe_config,
				   struct drm_connector_state *conn_state)
{
	struct drm_display_mode *adjusted_mode =
		&pipe_config->base.adjusted_mode;

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return false;

	pipe_config->has_pch_encoder = true;

	return true;
}