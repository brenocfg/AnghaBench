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
typedef  int u32 ;
struct link_vars {scalar_t__ flow_ctrl; int phy_flags; } ;
struct link_params {scalar_t__ req_fc_auto_adv; struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ req_flow_ctrl; scalar_t__ req_line_speed; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNX2X_FLOW_CTRL_AUTO ; 
 scalar_t__ BNX2X_FLOW_CTRL_NONE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int MDIO_AN_CL73_OR_37_COMPLETE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int PHY_SGMII_FLAG ; 
 scalar_t__ SPEED_AUTO_NEG ; 
 scalar_t__ bnx2x_direct_parallel_detect_used (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_update_adv_fc (struct bnx2x_phy*,struct link_params*,struct link_vars*,int) ; 

__attribute__((used)) static void bnx2x_flow_ctrl_resolve(struct bnx2x_phy *phy,
				    struct link_params *params,
				    struct link_vars *vars,
				    u32 gp_status)
{
	struct bnx2x *bp = params->bp;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;

	/* Resolve from gp_status in case of AN complete and not sgmii */
	if (phy->req_flow_ctrl != BNX2X_FLOW_CTRL_AUTO) {
		/* Update the advertised flow-controled of LD/LP in AN */
		if (phy->req_line_speed == SPEED_AUTO_NEG)
			bnx2x_update_adv_fc(phy, params, vars, gp_status);
		/* But set the flow-control result as the requested one */
		vars->flow_ctrl = phy->req_flow_ctrl;
	} else if (phy->req_line_speed != SPEED_AUTO_NEG)
		vars->flow_ctrl = params->req_fc_auto_adv;
	else if ((gp_status & MDIO_AN_CL73_OR_37_COMPLETE) &&
		 (!(vars->phy_flags & PHY_SGMII_FLAG))) {
		if (bnx2x_direct_parallel_detect_used(phy, params)) {
			vars->flow_ctrl = params->req_fc_auto_adv;
			return;
		}
		bnx2x_update_adv_fc(phy, params, vars, gp_status);
	}
	DP(NETIF_MSG_LINK, "flow_ctrl 0x%x\n", vars->flow_ctrl);
}