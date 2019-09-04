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
struct msm_dsi_phy_shared_timings {int dummy; } ;
struct msm_dsi_phy_clk_request {int dummy; } ;
struct msm_dsi {int /*<<< orphan*/  phy; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int IS_DUAL_DSI () ; 
 int /*<<< orphan*/  msm_dsi_host_get_phy_clk_req (int /*<<< orphan*/ ,struct msm_dsi_phy_clk_request*,int) ; 
 int msm_dsi_phy_enable (int /*<<< orphan*/ ,int,struct msm_dsi_phy_clk_request*) ; 
 int /*<<< orphan*/  msm_dsi_phy_get_shared_timings (int /*<<< orphan*/ ,struct msm_dsi_phy_shared_timings*) ; 

__attribute__((used)) static int enable_phy(struct msm_dsi *msm_dsi, int src_pll_id,
		      struct msm_dsi_phy_shared_timings *shared_timings)
{
	struct msm_dsi_phy_clk_request clk_req;
	int ret;
	bool is_dual_dsi = IS_DUAL_DSI();

	msm_dsi_host_get_phy_clk_req(msm_dsi->host, &clk_req, is_dual_dsi);

	ret = msm_dsi_phy_enable(msm_dsi->phy, src_pll_id, &clk_req);
	msm_dsi_phy_get_shared_timings(msm_dsi->phy, shared_timings);

	return ret;
}