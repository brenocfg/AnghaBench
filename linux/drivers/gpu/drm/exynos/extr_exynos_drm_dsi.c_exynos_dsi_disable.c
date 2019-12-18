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
struct exynos_dsi {int state; int /*<<< orphan*/  dev; int /*<<< orphan*/  out_bridge; int /*<<< orphan*/  panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int DSIM_STATE_ENABLED ; 
 int DSIM_STATE_VIDOUT_AVAILABLE ; 
 int /*<<< orphan*/  drm_bridge_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_post_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 struct exynos_dsi* encoder_to_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  exynos_dsi_set_display_enable (struct exynos_dsi*,int) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_dsi_disable(struct drm_encoder *encoder)
{
	struct exynos_dsi *dsi = encoder_to_dsi(encoder);

	if (!(dsi->state & DSIM_STATE_ENABLED))
		return;

	dsi->state &= ~DSIM_STATE_VIDOUT_AVAILABLE;

	drm_panel_disable(dsi->panel);
	drm_bridge_disable(dsi->out_bridge);
	exynos_dsi_set_display_enable(dsi, false);
	drm_panel_unprepare(dsi->panel);
	drm_bridge_post_disable(dsi->out_bridge);
	dsi->state &= ~DSIM_STATE_ENABLED;
	pm_runtime_put_sync(dsi->dev);
}