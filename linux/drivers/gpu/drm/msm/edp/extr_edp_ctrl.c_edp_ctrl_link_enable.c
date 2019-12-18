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
typedef  int /*<<< orphan*/  u32 ;
struct edp_ctrl {int /*<<< orphan*/  phy; int /*<<< orphan*/  pixel_rate; int /*<<< orphan*/  lane_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_CLK_MASK_LINK_CHAN ; 
 int /*<<< orphan*/  edp_clk_disable (struct edp_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edp_clk_enable (struct edp_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edp_config_ctrl (struct edp_ctrl*) ; 
 int /*<<< orphan*/  edp_mainlink_ctrl (struct edp_ctrl*,int) ; 
 int /*<<< orphan*/  edp_sw_mvid_nvid (struct edp_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_edp_ctrl_pixel_clock_valid (struct edp_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_edp_phy_lane_power_ctrl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_edp_phy_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_edp_phy_vm_pe_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void edp_ctrl_link_enable(struct edp_ctrl *ctrl, int enable)
{
	u32 m, n;

	if (enable) {
		/* Enable link channel clocks */
		edp_clk_enable(ctrl, EDP_CLK_MASK_LINK_CHAN);

		msm_edp_phy_lane_power_ctrl(ctrl->phy, true, ctrl->lane_cnt);

		msm_edp_phy_vm_pe_init(ctrl->phy);

		/* Make sure phy is programed */
		wmb();
		msm_edp_phy_ready(ctrl->phy);

		edp_config_ctrl(ctrl);
		msm_edp_ctrl_pixel_clock_valid(ctrl, ctrl->pixel_rate, &m, &n);
		edp_sw_mvid_nvid(ctrl, m, n);
		edp_mainlink_ctrl(ctrl, 1);
	} else {
		edp_mainlink_ctrl(ctrl, 0);

		msm_edp_phy_lane_power_ctrl(ctrl->phy, false, 0);
		edp_clk_disable(ctrl, EDP_CLK_MASK_LINK_CHAN);
	}
}