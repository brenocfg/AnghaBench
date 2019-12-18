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
struct sti_hdmi {int /*<<< orphan*/  clk_phy; int /*<<< orphan*/  clk_pix; int /*<<< orphan*/  mode; } ;
struct drm_display_mode {int clock; } ;
struct drm_bridge {struct sti_hdmi* driver_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct drm_display_mode const*,int) ; 

__attribute__((used)) static void sti_hdmi_set_mode(struct drm_bridge *bridge,
			      const struct drm_display_mode *mode,
			      const struct drm_display_mode *adjusted_mode)
{
	struct sti_hdmi *hdmi = bridge->driver_private;
	int ret;

	DRM_DEBUG_DRIVER("\n");

	/* Copy the drm display mode in the connector local structure */
	memcpy(&hdmi->mode, mode, sizeof(struct drm_display_mode));

	/* Update clock framerate according to the selected mode */
	ret = clk_set_rate(hdmi->clk_pix, mode->clock * 1000);
	if (ret < 0) {
		DRM_ERROR("Cannot set rate (%dHz) for hdmi_pix clk\n",
			  mode->clock * 1000);
		return;
	}
	ret = clk_set_rate(hdmi->clk_phy, mode->clock * 1000);
	if (ret < 0) {
		DRM_ERROR("Cannot set rate (%dHz) for hdmi_rejection_pll clk\n",
			  mode->clock * 1000);
		return;
	}
}