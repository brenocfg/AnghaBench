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
struct link_vars {int /*<<< orphan*/  link_status; void* flow_ctrl; } ;
struct link_params {void* req_fc_auto_adv; struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 void* BNX2X_FLOW_CTRL_BOTH ; 
 void* BNX2X_FLOW_CTRL_NONE ; 
 void* BNX2X_FLOW_CTRL_RX ; 
 void* BNX2X_FLOW_CTRL_TX ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 

__attribute__((used)) static void bnx2x_pause_resolve(struct bnx2x_phy *phy,
				struct link_params *params,
				struct link_vars *vars,
				u32 pause_result)
{
	struct bnx2x *bp = params->bp;
						/*  LD	    LP	 */
	switch (pause_result) {			/* ASYM P ASYM P */
	case 0xb:				/*   1  0   1  1 */
		DP(NETIF_MSG_LINK, "Flow Control: TX only\n");
		vars->flow_ctrl = BNX2X_FLOW_CTRL_TX;
		break;

	case 0xe:				/*   1  1   1  0 */
		DP(NETIF_MSG_LINK, "Flow Control: RX only\n");
		vars->flow_ctrl = BNX2X_FLOW_CTRL_RX;
		break;

	case 0x5:				/*   0  1   0  1 */
	case 0x7:				/*   0  1   1  1 */
	case 0xd:				/*   1  1   0  1 */
	case 0xf:				/*   1  1   1  1 */
		/* If the user selected to advertise RX ONLY,
		 * although we advertised both, need to enable
		 * RX only.
		 */
		if (params->req_fc_auto_adv == BNX2X_FLOW_CTRL_BOTH) {
			DP(NETIF_MSG_LINK, "Flow Control: RX & TX\n");
			vars->flow_ctrl = BNX2X_FLOW_CTRL_BOTH;
		} else {
			DP(NETIF_MSG_LINK, "Flow Control: RX only\n");
			vars->flow_ctrl = BNX2X_FLOW_CTRL_RX;
		}
		break;

	default:
		DP(NETIF_MSG_LINK, "Flow Control: None\n");
		vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
		break;
	}
	if (pause_result & (1<<0))
		vars->link_status |= LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE;
	if (pause_result & (1<<1))
		vars->link_status |= LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE;

}