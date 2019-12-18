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
typedef  int u32 ;
struct link_vars {scalar_t__ phy_link_up; } ;
struct link_params {int port; scalar_t__ switch_cfg; int lane_config; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ NIG_REG_STATUS_INTERRUPT_PORT0 ; 
 int NIG_STATUS_SERDES0_LINK_STATUS ; 
 int NIG_STATUS_XGXS0_LINK10G ; 
 int NIG_STATUS_XGXS0_LINK_STATUS ; 
 int NIG_STATUS_XGXS0_LINK_STATUS_SIZE ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT ; 
 scalar_t__ SWITCH_CFG_10G ; 
 scalar_t__ USES_WARPCORE (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_bits_dis (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  bnx2x_bits_en (struct bnx2x*,scalar_t__,int) ; 

__attribute__((used)) static void bnx2x_link_int_ack(struct link_params *params,
			       struct link_vars *vars, u8 is_10g_plus)
{
	struct bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 mask;
	/* First reset all status we assume only one line will be
	 * change at a time
	 */
	bnx2x_bits_dis(bp, NIG_REG_STATUS_INTERRUPT_PORT0 + port*4,
		       (NIG_STATUS_XGXS0_LINK10G |
			NIG_STATUS_XGXS0_LINK_STATUS |
			NIG_STATUS_SERDES0_LINK_STATUS));
	if (vars->phy_link_up) {
		if (USES_WARPCORE(bp))
			mask = NIG_STATUS_XGXS0_LINK_STATUS;
		else {
			if (is_10g_plus)
				mask = NIG_STATUS_XGXS0_LINK10G;
			else if (params->switch_cfg == SWITCH_CFG_10G) {
				/* Disable the link interrupt by writing 1 to
				 * the relevant lane in the status register
				 */
				u32 ser_lane =
					((params->lane_config &
				    PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
				    PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);
				mask = ((1 << ser_lane) <<
				       NIG_STATUS_XGXS0_LINK_STATUS_SIZE);
			} else
				mask = NIG_STATUS_SERDES0_LINK_STATUS;
		}
		DP(NETIF_MSG_LINK, "Ack link up interrupt with mask 0x%x\n",
			       mask);
		bnx2x_bits_en(bp,
			      NIG_REG_STATUS_INTERRUPT_PORT0 + port*4,
			      mask);
	}
}