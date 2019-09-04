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
struct intel_sdvo {int pixel_clock_min; int pixel_clock_max; TYPE_1__* sdvo_lvds_fixed_mode; scalar_t__ is_lvds; } ;
struct drm_display_mode {int flags; int clock; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_4__ {int max_dotclk_freq; } ;
struct TYPE_3__ {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_LOW ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_OK ; 
 int MODE_PANEL ; 
 struct intel_sdvo* intel_attached_sdvo (struct drm_connector*) ; 
 TYPE_2__* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_mode_status
intel_sdvo_mode_valid(struct drm_connector *connector,
		      struct drm_display_mode *mode)
{
	struct intel_sdvo *intel_sdvo = intel_attached_sdvo(connector);
	int max_dotclk = to_i915(connector->dev)->max_dotclk_freq;

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	if (intel_sdvo->pixel_clock_min > mode->clock)
		return MODE_CLOCK_LOW;

	if (intel_sdvo->pixel_clock_max < mode->clock)
		return MODE_CLOCK_HIGH;

	if (mode->clock > max_dotclk)
		return MODE_CLOCK_HIGH;

	if (intel_sdvo->is_lvds) {
		if (mode->hdisplay > intel_sdvo->sdvo_lvds_fixed_mode->hdisplay)
			return MODE_PANEL;

		if (mode->vdisplay > intel_sdvo->sdvo_lvds_fixed_mode->vdisplay)
			return MODE_PANEL;
	}

	return MODE_OK;
}