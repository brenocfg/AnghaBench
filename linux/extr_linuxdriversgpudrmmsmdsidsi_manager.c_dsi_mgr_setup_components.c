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
struct msm_dsi_pll {int dummy; } ;
struct msm_dsi {int /*<<< orphan*/  host; int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 int DSI_CLOCK_MASTER ; 
 int DSI_CLOCK_SLAVE ; 
 int /*<<< orphan*/  IS_DUAL_DSI () ; 
 scalar_t__ IS_ERR (struct msm_dsi_pll*) ; 
 scalar_t__ IS_MASTER_DSI_LINK (int) ; 
 int /*<<< orphan*/  MSM_DSI_PHY_MASTER ; 
 int /*<<< orphan*/  MSM_DSI_PHY_SLAVE ; 
 int /*<<< orphan*/  MSM_DSI_PHY_STANDALONE ; 
 int PTR_ERR (struct msm_dsi_pll*) ; 
 struct msm_dsi* dsi_mgr_get_dsi (int) ; 
 struct msm_dsi* dsi_mgr_get_other_dsi (int) ; 
 int msm_dsi_host_register (int /*<<< orphan*/ ,int) ; 
 int msm_dsi_host_set_src_pll (int /*<<< orphan*/ ,struct msm_dsi_pll*) ; 
 struct msm_dsi_pll* msm_dsi_phy_get_pll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_dsi_phy_set_usecase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_mgr_setup_components(int id)
{
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	struct msm_dsi *other_dsi = dsi_mgr_get_other_dsi(id);
	struct msm_dsi *clk_master_dsi = dsi_mgr_get_dsi(DSI_CLOCK_MASTER);
	struct msm_dsi *clk_slave_dsi = dsi_mgr_get_dsi(DSI_CLOCK_SLAVE);
	struct msm_dsi_pll *src_pll;
	int ret;

	if (!IS_DUAL_DSI()) {
		ret = msm_dsi_host_register(msm_dsi->host, true);
		if (ret)
			return ret;

		msm_dsi_phy_set_usecase(msm_dsi->phy, MSM_DSI_PHY_STANDALONE);
		src_pll = msm_dsi_phy_get_pll(msm_dsi->phy);
		if (IS_ERR(src_pll))
			return PTR_ERR(src_pll);
		ret = msm_dsi_host_set_src_pll(msm_dsi->host, src_pll);
	} else if (!other_dsi) {
		ret = 0;
	} else {
		struct msm_dsi *master_link_dsi = IS_MASTER_DSI_LINK(id) ?
							msm_dsi : other_dsi;
		struct msm_dsi *slave_link_dsi = IS_MASTER_DSI_LINK(id) ?
							other_dsi : msm_dsi;
		/* Register slave host first, so that slave DSI device
		 * has a chance to probe, and do not block the master
		 * DSI device's probe.
		 * Also, do not check defer for the slave host,
		 * because only master DSI device adds the panel to global
		 * panel list. The panel's device is the master DSI device.
		 */
		ret = msm_dsi_host_register(slave_link_dsi->host, false);
		if (ret)
			return ret;
		ret = msm_dsi_host_register(master_link_dsi->host, true);
		if (ret)
			return ret;

		/* PLL0 is to drive both 2 DSI link clocks in Dual DSI mode. */
		msm_dsi_phy_set_usecase(clk_master_dsi->phy,
					MSM_DSI_PHY_MASTER);
		msm_dsi_phy_set_usecase(clk_slave_dsi->phy,
					MSM_DSI_PHY_SLAVE);
		src_pll = msm_dsi_phy_get_pll(clk_master_dsi->phy);
		if (IS_ERR(src_pll))
			return PTR_ERR(src_pll);
		ret = msm_dsi_host_set_src_pll(msm_dsi->host, src_pll);
		if (ret)
			return ret;
		ret = msm_dsi_host_set_src_pll(other_dsi->host, src_pll);
	}

	return ret;
}