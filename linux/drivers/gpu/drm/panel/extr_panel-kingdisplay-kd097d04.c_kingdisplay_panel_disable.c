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
struct kingdisplay_panel {int enabled; int /*<<< orphan*/  link; int /*<<< orphan*/  backlight; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  backlight_disable (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_display_off (int /*<<< orphan*/ ) ; 
 struct kingdisplay_panel* to_kingdisplay_panel (struct drm_panel*) ; 

__attribute__((used)) static int kingdisplay_panel_disable(struct drm_panel *panel)
{
	struct kingdisplay_panel *kingdisplay = to_kingdisplay_panel(panel);
	int err;

	if (!kingdisplay->enabled)
		return 0;

	backlight_disable(kingdisplay->backlight);

	err = mipi_dsi_dcs_set_display_off(kingdisplay->link);
	if (err < 0)
		DRM_DEV_ERROR(panel->dev, "failed to set display off: %d\n",
			      err);

	kingdisplay->enabled = false;

	return 0;
}