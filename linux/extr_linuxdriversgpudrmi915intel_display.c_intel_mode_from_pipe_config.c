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
struct TYPE_3__ {int /*<<< orphan*/  crtc_clock; int /*<<< orphan*/  flags; int /*<<< orphan*/  crtc_vsync_end; int /*<<< orphan*/  crtc_vsync_start; int /*<<< orphan*/  crtc_vtotal; int /*<<< orphan*/  crtc_vdisplay; int /*<<< orphan*/  crtc_hsync_end; int /*<<< orphan*/  crtc_hsync_start; int /*<<< orphan*/  crtc_htotal; int /*<<< orphan*/  crtc_hdisplay; } ;
struct TYPE_4__ {TYPE_1__ adjusted_mode; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct drm_display_mode {int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  hsync; int /*<<< orphan*/  clock; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hsync_end; int /*<<< orphan*/  hsync_start; int /*<<< orphan*/  htotal; int /*<<< orphan*/  hdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_TYPE_DRIVER ; 
 int /*<<< orphan*/  drm_mode_hsync (struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_vrefresh (struct drm_display_mode*) ; 

void intel_mode_from_pipe_config(struct drm_display_mode *mode,
				 struct intel_crtc_state *pipe_config)
{
	mode->hdisplay = pipe_config->base.adjusted_mode.crtc_hdisplay;
	mode->htotal = pipe_config->base.adjusted_mode.crtc_htotal;
	mode->hsync_start = pipe_config->base.adjusted_mode.crtc_hsync_start;
	mode->hsync_end = pipe_config->base.adjusted_mode.crtc_hsync_end;

	mode->vdisplay = pipe_config->base.adjusted_mode.crtc_vdisplay;
	mode->vtotal = pipe_config->base.adjusted_mode.crtc_vtotal;
	mode->vsync_start = pipe_config->base.adjusted_mode.crtc_vsync_start;
	mode->vsync_end = pipe_config->base.adjusted_mode.crtc_vsync_end;

	mode->flags = pipe_config->base.adjusted_mode.flags;
	mode->type = DRM_MODE_TYPE_DRIVER;

	mode->clock = pipe_config->base.adjusted_mode.crtc_clock;

	mode->hsync = drm_mode_hsync(mode);
	mode->vrefresh = drm_mode_vrefresh(mode);
	drm_mode_set_name(mode);
}