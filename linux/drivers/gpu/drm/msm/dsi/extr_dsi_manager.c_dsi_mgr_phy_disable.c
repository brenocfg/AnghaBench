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
struct msm_dsi {int phy_enabled; int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 int DSI_CLOCK_MASTER ; 
 int DSI_CLOCK_SLAVE ; 
 scalar_t__ IS_DUAL_DSI () ; 
 struct msm_dsi* dsi_mgr_get_dsi (int) ; 
 int /*<<< orphan*/  msm_dsi_phy_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_mgr_phy_disable(int id)
{
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	struct msm_dsi *mdsi = dsi_mgr_get_dsi(DSI_CLOCK_MASTER);
	struct msm_dsi *sdsi = dsi_mgr_get_dsi(DSI_CLOCK_SLAVE);

	/* disable DSI phy
	 * In dual-dsi configuration, the phy should be disabled for the
	 * first controller only when the second controller is disabled.
	 */
	msm_dsi->phy_enabled = false;
	if (IS_DUAL_DSI() && mdsi && sdsi) {
		if (!mdsi->phy_enabled && !sdsi->phy_enabled) {
			msm_dsi_phy_disable(sdsi->phy);
			msm_dsi_phy_disable(mdsi->phy);
		}
	} else {
		msm_dsi_phy_disable(msm_dsi->phy);
	}
}