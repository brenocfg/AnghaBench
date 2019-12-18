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
typedef  int u8 ;
struct link_vars {scalar_t__ flow_ctrl; int link_status; } ;
struct link_params {scalar_t__ req_fc_auto_adv; } ;
struct bnx2x_phy {scalar_t__ req_flow_ctrl; scalar_t__ req_line_speed; } ;

/* Variables and functions */
 scalar_t__ BNX2X_FLOW_CTRL_AUTO ; 
 scalar_t__ BNX2X_FLOW_CTRL_NONE ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 scalar_t__ SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  bnx2x_ext_phy_update_adv_fc (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 

__attribute__((used)) static u8 bnx2x_ext_phy_resolve_fc(struct bnx2x_phy *phy,
				   struct link_params *params,
				   struct link_vars *vars)
{
	u8 ret = 0;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	if (phy->req_flow_ctrl != BNX2X_FLOW_CTRL_AUTO) {
		/* Update the advertised flow-controled of LD/LP in AN */
		if (phy->req_line_speed == SPEED_AUTO_NEG)
			bnx2x_ext_phy_update_adv_fc(phy, params, vars);
		/* But set the flow-control result as the requested one */
		vars->flow_ctrl = phy->req_flow_ctrl;
	} else if (phy->req_line_speed != SPEED_AUTO_NEG)
		vars->flow_ctrl = params->req_fc_auto_adv;
	else if (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) {
		ret = 1;
		bnx2x_ext_phy_update_adv_fc(phy, params, vars);
	}
	return ret;
}