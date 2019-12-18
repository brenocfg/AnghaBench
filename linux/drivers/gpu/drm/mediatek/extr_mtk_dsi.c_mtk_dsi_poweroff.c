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
struct mtk_dsi {scalar_t__ refcount; int /*<<< orphan*/  phy; int /*<<< orphan*/  digital_clk; int /*<<< orphan*/  engine_clk; scalar_t__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  VM_DONE_INT_FLAG ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_panel_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  mtk_dsi_clk_ulp_mode_enter (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_disable (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_lane0_ulp_mode_enter (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_reset_engine (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_stop (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_switch_to_cmd_mode (struct mtk_dsi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dsi_poweroff(struct mtk_dsi *dsi)
{
	if (WARN_ON(dsi->refcount == 0))
		return;

	if (--dsi->refcount != 0)
		return;

	/*
	 * mtk_dsi_stop() and mtk_dsi_start() is asymmetric, since
	 * mtk_dsi_stop() should be called after mtk_drm_crtc_atomic_disable(),
	 * which needs irq for vblank, and mtk_dsi_stop() will disable irq.
	 * mtk_dsi_start() needs to be called in mtk_output_dsi_enable(),
	 * after dsi is fully set.
	 */
	mtk_dsi_stop(dsi);

	if (!mtk_dsi_switch_to_cmd_mode(dsi, VM_DONE_INT_FLAG, 500)) {
		if (dsi->panel) {
			if (drm_panel_unprepare(dsi->panel)) {
				DRM_ERROR("failed to unprepare the panel\n");
				return;
			}
		}
	}

	mtk_dsi_reset_engine(dsi);
	mtk_dsi_lane0_ulp_mode_enter(dsi);
	mtk_dsi_clk_ulp_mode_enter(dsi);

	mtk_dsi_disable(dsi);

	clk_disable_unprepare(dsi->engine_clk);
	clk_disable_unprepare(dsi->digital_clk);

	phy_power_off(dsi->phy);
}