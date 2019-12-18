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
struct sun6i_dsi {int /*<<< orphan*/  dev; int /*<<< orphan*/  dphy; int /*<<< orphan*/  panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 struct sun6i_dsi* encoder_to_sun6i_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun6i_dsi_encoder_disable(struct drm_encoder *encoder)
{
	struct sun6i_dsi *dsi = encoder_to_sun6i_dsi(encoder);

	DRM_DEBUG_DRIVER("Disabling DSI output\n");

	if (!IS_ERR(dsi->panel)) {
		drm_panel_disable(dsi->panel);
		drm_panel_unprepare(dsi->panel);
	}

	phy_power_off(dsi->dphy);
	phy_exit(dsi->dphy);

	pm_runtime_put(dsi->dev);
}