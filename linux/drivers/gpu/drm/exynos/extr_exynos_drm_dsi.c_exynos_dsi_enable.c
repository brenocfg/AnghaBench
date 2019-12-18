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
struct exynos_dsi {int state; int /*<<< orphan*/  dev; scalar_t__ panel; int /*<<< orphan*/  out_bridge; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int DSIM_STATE_ENABLED ; 
 int DSIM_STATE_VIDOUT_AVAILABLE ; 
 int /*<<< orphan*/  drm_bridge_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_pre_enable (int /*<<< orphan*/ ) ; 
 int drm_panel_enable (scalar_t__) ; 
 int drm_panel_prepare (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_unprepare (scalar_t__) ; 
 struct exynos_dsi* encoder_to_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  exynos_dsi_set_display_enable (struct exynos_dsi*,int) ; 
 int /*<<< orphan*/  exynos_dsi_set_display_mode (struct exynos_dsi*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_dsi_enable(struct drm_encoder *encoder)
{
	struct exynos_dsi *dsi = encoder_to_dsi(encoder);
	int ret;

	if (dsi->state & DSIM_STATE_ENABLED)
		return;

	pm_runtime_get_sync(dsi->dev);
	dsi->state |= DSIM_STATE_ENABLED;

	if (dsi->panel) {
		ret = drm_panel_prepare(dsi->panel);
		if (ret < 0)
			goto err_put_sync;
	} else {
		drm_bridge_pre_enable(dsi->out_bridge);
	}

	exynos_dsi_set_display_mode(dsi);
	exynos_dsi_set_display_enable(dsi, true);

	if (dsi->panel) {
		ret = drm_panel_enable(dsi->panel);
		if (ret < 0)
			goto err_display_disable;
	} else {
		drm_bridge_enable(dsi->out_bridge);
	}

	dsi->state |= DSIM_STATE_VIDOUT_AVAILABLE;
	return;

err_display_disable:
	exynos_dsi_set_display_enable(dsi, false);
	drm_panel_unprepare(dsi->panel);

err_put_sync:
	dsi->state &= ~DSIM_STATE_ENABLED;
	pm_runtime_put(dsi->dev);
}