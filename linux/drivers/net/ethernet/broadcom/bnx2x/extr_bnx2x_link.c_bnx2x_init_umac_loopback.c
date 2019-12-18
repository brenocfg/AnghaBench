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
struct link_vars {int link_up; int /*<<< orphan*/  phy_flags; int /*<<< orphan*/  mac_type; int /*<<< orphan*/  flow_ctrl; int /*<<< orphan*/  duplex; int /*<<< orphan*/  line_speed; } ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FLOW_CTRL_NONE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  MAC_TYPE_UMAC ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 int /*<<< orphan*/  PHY_XGXS_FLAG ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  bnx2x_umac_enable (struct link_params*,struct link_vars*,int) ; 

__attribute__((used)) static void bnx2x_init_umac_loopback(struct link_params *params,
				     struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	vars->link_up = 1;
	vars->line_speed = SPEED_1000;
	vars->duplex = DUPLEX_FULL;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	vars->mac_type = MAC_TYPE_UMAC;
	vars->phy_flags = PHY_XGXS_FLAG;
	bnx2x_umac_enable(params, vars, 1);

	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
}