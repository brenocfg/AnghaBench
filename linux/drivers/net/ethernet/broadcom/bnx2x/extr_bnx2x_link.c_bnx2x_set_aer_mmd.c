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
typedef  int u16 ;
struct link_params {int lane_config; struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ type; int addr; int flags; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E2 (struct bnx2x*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int FLAGS_WC_DUAL_MODE ; 
 int /*<<< orphan*/  MDIO_AER_BLOCK_AER_REG ; 
 int /*<<< orphan*/  MDIO_REG_BANK_AER_BLOCK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT ; 
 scalar_t__ USES_WARPCORE (struct bnx2x*) ; 
 int bnx2x_get_warpcore_lane (struct bnx2x_phy*,struct link_params*) ; 

__attribute__((used)) static void bnx2x_set_aer_mmd(struct link_params *params,
			      struct bnx2x_phy *phy)
{
	u32 ser_lane;
	u16 offset, aer_val;
	struct bnx2x *bp = params->bp;
	ser_lane = ((params->lane_config &
		     PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
		     PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);

	offset = (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT) ?
		(phy->addr + ser_lane) : 0;

	if (USES_WARPCORE(bp)) {
		aer_val = bnx2x_get_warpcore_lane(phy, params);
		/* In Dual-lane mode, two lanes are joined together,
		 * so in order to configure them, the AER broadcast method is
		 * used here.
		 * 0x200 is the broadcast address for lanes 0,1
		 * 0x201 is the broadcast address for lanes 2,3
		 */
		if (phy->flags & FLAGS_WC_DUAL_MODE)
			aer_val = (aer_val >> 1) | 0x200;
	} else if (CHIP_IS_E2(bp))
		aer_val = 0x3800 + offset - 1;
	else
		aer_val = 0x3800 + offset;

	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, aer_val);

}