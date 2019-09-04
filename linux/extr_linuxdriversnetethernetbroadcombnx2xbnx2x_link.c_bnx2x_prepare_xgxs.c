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
struct link_vars {int /*<<< orphan*/  ieee_fc; int /*<<< orphan*/  phy_flags; } ;
struct link_params {int dummy; } ;
struct bnx2x_phy {scalar_t__ req_line_speed; scalar_t__ speed_cap_mask; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_SGMII_FLAG ; 
 int /*<<< orphan*/  PHY_XGXS_FLAG ; 
 scalar_t__ PORT_HW_CFG_SERDES_EXT_PHY_TYPE_DIRECT_SD ; 
 scalar_t__ PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL ; 
 scalar_t__ PORT_HW_CFG_SPEED_CAPABILITY_D0_1G ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  bnx2x_calc_ieee_aneg_adv (struct bnx2x_phy*,struct link_params*,int /*<<< orphan*/ *) ; 
 int bnx2x_reset_unicore (struct link_params*,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_aer_mmd (struct link_params*,struct bnx2x_phy*) ; 
 int /*<<< orphan*/  bnx2x_set_master_ln (struct link_params*,struct bnx2x_phy*) ; 
 int /*<<< orphan*/  bnx2x_set_swap_lanes (struct link_params*,struct bnx2x_phy*) ; 

__attribute__((used)) static int bnx2x_prepare_xgxs(struct bnx2x_phy *phy,
			  struct link_params *params,
			  struct link_vars *vars)
{
	int rc;
	vars->phy_flags |= PHY_XGXS_FLAG;
	if ((phy->req_line_speed &&
	     ((phy->req_line_speed == SPEED_100) ||
	      (phy->req_line_speed == SPEED_10))) ||
	    (!phy->req_line_speed &&
	     (phy->speed_cap_mask >=
	      PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL) &&
	     (phy->speed_cap_mask <
	      PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)) ||
	    (phy->type == PORT_HW_CFG_SERDES_EXT_PHY_TYPE_DIRECT_SD))
		vars->phy_flags |= PHY_SGMII_FLAG;
	else
		vars->phy_flags &= ~PHY_SGMII_FLAG;

	bnx2x_calc_ieee_aneg_adv(phy, params, &vars->ieee_fc);
	bnx2x_set_aer_mmd(params, phy);
	if (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT)
		bnx2x_set_master_ln(params, phy);

	rc = bnx2x_reset_unicore(params, phy, 0);
	/* Reset the SerDes and wait for reset bit return low */
	if (rc)
		return rc;

	bnx2x_set_aer_mmd(params, phy);
	/* Setting the masterLn_def again after the reset */
	if (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT) {
		bnx2x_set_master_ln(params, phy);
		bnx2x_set_swap_lanes(params, phy);
	}

	return rc;
}