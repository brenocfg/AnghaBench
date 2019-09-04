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
struct edp_ctrl {int /*<<< orphan*/  phy; int /*<<< orphan*/  aux; int /*<<< orphan*/  panel_en_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_CLK_MASK_AUX_CHAN ; 
 int /*<<< orphan*/  edp_clk_disable (struct edp_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edp_clk_enable (struct edp_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edp_regulator_disable (struct edp_ctrl*) ; 
 int /*<<< orphan*/  edp_regulator_enable (struct edp_ctrl*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msm_edp_aux_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msm_edp_phy_ctrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void edp_ctrl_phy_aux_enable(struct edp_ctrl *ctrl, int enable)
{
	if (enable) {
		edp_regulator_enable(ctrl);
		edp_clk_enable(ctrl, EDP_CLK_MASK_AUX_CHAN);
		msm_edp_phy_ctrl(ctrl->phy, 1);
		msm_edp_aux_ctrl(ctrl->aux, 1);
		gpiod_set_value(ctrl->panel_en_gpio, 1);
	} else {
		gpiod_set_value(ctrl->panel_en_gpio, 0);
		msm_edp_aux_ctrl(ctrl->aux, 0);
		msm_edp_phy_ctrl(ctrl->phy, 0);
		edp_clk_disable(ctrl, EDP_CLK_MASK_AUX_CHAN);
		edp_regulator_disable(ctrl);
	}
}