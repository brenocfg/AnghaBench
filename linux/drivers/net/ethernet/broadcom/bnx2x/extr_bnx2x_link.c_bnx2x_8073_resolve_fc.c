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
typedef  int u16 ;
struct link_vars {scalar_t__ flow_ctrl; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ req_line_speed; scalar_t__ req_flow_ctrl; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNX2X_FLOW_CTRL_NONE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_CL37_FC_LD ; 
 int /*<<< orphan*/  MDIO_AN_REG_CL37_FC_LP ; 
 int MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ bnx2x_ext_phy_resolve_fc (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_pause_resolve (struct bnx2x_phy*,struct link_params*,struct link_vars*,int) ; 

__attribute__((used)) static void bnx2x_8073_resolve_fc(struct bnx2x_phy *phy,
				  struct link_params *params,
				  struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	if (phy->req_line_speed == SPEED_10 ||
	    phy->req_line_speed == SPEED_100) {
		vars->flow_ctrl = phy->req_flow_ctrl;
		return;
	}

	if (bnx2x_ext_phy_resolve_fc(phy, params, vars) &&
	    (vars->flow_ctrl == BNX2X_FLOW_CTRL_NONE)) {
		u16 pause_result;
		u16 ld_pause;		/* local */
		u16 lp_pause;		/* link partner */
		bnx2x_cl45_read(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_CL37_FC_LD, &ld_pause);

		bnx2x_cl45_read(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_CL37_FC_LP, &lp_pause);
		pause_result = (ld_pause &
				MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH) >> 5;
		pause_result |= (lp_pause &
				 MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH) >> 7;

		bnx2x_pause_resolve(phy, params, vars, pause_result);
		DP(NETIF_MSG_LINK, "Ext PHY CL37 pause result 0x%x\n",
			   pause_result);
	}
}