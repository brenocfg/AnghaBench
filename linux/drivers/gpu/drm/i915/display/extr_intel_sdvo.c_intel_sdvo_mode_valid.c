#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct drm_display_mode* fixed_mode; } ;
struct TYPE_5__ {TYPE_1__ panel; } ;
struct intel_sdvo_connector {TYPE_2__ base; } ;
struct intel_sdvo {int pixel_clock_min; int pixel_clock_max; } ;
struct drm_display_mode {int flags; int clock; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_6__ {int max_dotclk_freq; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 scalar_t__ IS_LVDS (struct intel_sdvo_connector*) ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_LOW ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_OK ; 
 int MODE_PANEL ; 
 struct intel_sdvo* intel_attached_sdvo (struct drm_connector*) ; 
 TYPE_3__* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_sdvo_connector* to_intel_sdvo_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_mode_status
intel_sdvo_mode_valid(struct drm_connector *connector,
		      struct drm_display_mode *mode)
{
	struct intel_sdvo *intel_sdvo = intel_attached_sdvo(connector);
	struct intel_sdvo_connector *intel_sdvo_connector =
		to_intel_sdvo_connector(connector);
	int max_dotclk = to_i915(connector->dev)->max_dotclk_freq;

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	if (intel_sdvo->pixel_clock_min > mode->clock)
		return MODE_CLOCK_LOW;

	if (intel_sdvo->pixel_clock_max < mode->clock)
		return MODE_CLOCK_HIGH;

	if (mode->clock > max_dotclk)
		return MODE_CLOCK_HIGH;

	if (IS_LVDS(intel_sdvo_connector)) {
		const struct drm_display_mode *fixed_mode =
			intel_sdvo_connector->base.panel.fixed_mode;

		if (mode->hdisplay > fixed_mode->hdisplay)
			return MODE_PANEL;

		if (mode->vdisplay > fixed_mode->vdisplay)
			return MODE_PANEL;
	}

	return MODE_OK;
}