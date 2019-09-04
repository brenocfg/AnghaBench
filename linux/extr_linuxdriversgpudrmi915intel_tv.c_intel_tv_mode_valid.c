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
struct tv_mode {scalar_t__ refresh; } ;
struct drm_display_mode {int flags; int clock; } ;
struct drm_connector {int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {int max_dotclk_freq; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_RANGE ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_OK ; 
 int abs (scalar_t__) ; 
 int drm_mode_vrefresh (struct drm_display_mode*) ; 
 struct tv_mode* intel_tv_mode_find (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_mode_status
intel_tv_mode_valid(struct drm_connector *connector,
		    struct drm_display_mode *mode)
{
	const struct tv_mode *tv_mode = intel_tv_mode_find(connector->state);
	int max_dotclk = to_i915(connector->dev)->max_dotclk_freq;

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	if (mode->clock > max_dotclk)
		return MODE_CLOCK_HIGH;

	/* Ensure TV refresh is close to desired refresh */
	if (tv_mode && abs(tv_mode->refresh - drm_mode_vrefresh(mode) * 1000)
				< 1000)
		return MODE_OK;

	return MODE_CLOCK_RANGE;
}