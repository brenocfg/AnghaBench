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
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int speed_cap_mask; scalar_t__ type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL ; 
 int MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL_PARDET10G_EN ; 
 int /*<<< orphan*/  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK ; 
 int MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK_CNT ; 
 int /*<<< orphan*/  MDIO_REG_BANK_10G_PARALLEL_DETECT ; 
 int /*<<< orphan*/  MDIO_REG_BANK_SERDES_DIGITAL ; 
 int /*<<< orphan*/  MDIO_REG_BANK_XGXS_BLOCK2 ; 
 int /*<<< orphan*/  MDIO_SERDES_DIGITAL_A_1000X_CONTROL2 ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_PRL_DT_EN ; 
 int /*<<< orphan*/  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G ; 
 int MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_CX4_XGXS ; 
 int MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_HIGIG_XGXS ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_1G ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT ; 

__attribute__((used)) static void bnx2x_set_parallel_detection(struct bnx2x_phy *phy,
					 struct link_params *params)
{
	struct bnx2x *bp = params->bp;
	u16 control2;
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL2,
			  &control2);
	if (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)
		control2 |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_PRL_DT_EN;
	else
		control2 &= ~MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_PRL_DT_EN;
	DP(NETIF_MSG_LINK, "phy->speed_cap_mask = 0x%x, control2 = 0x%x\n",
		phy->speed_cap_mask, control2);
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL2,
			  control2);

	if ((phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT) &&
	     (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)) {
		DP(NETIF_MSG_LINK, "XGXS\n");

		CL22_WR_OVER_CL45(bp, phy,
				 MDIO_REG_BANK_10G_PARALLEL_DETECT,
				 MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK,
				 MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK_CNT);

		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_10G_PARALLEL_DETECT,
				  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL,
				  &control2);


		control2 |=
		    MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL_PARDET10G_EN;

		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_10G_PARALLEL_DETECT,
				  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL,
				  control2);

		/* Disable parallel detection of HiG */
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G,
				  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_CX4_XGXS |
				  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_HIGIG_XGXS);
	}
}