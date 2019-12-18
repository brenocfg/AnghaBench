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
struct link_vars {int line_speed; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ req_duplex; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_MII_CONTROL ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_AN_EN ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_100 ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_1000 ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_MASK ; 
 int /*<<< orphan*/  MDIO_REG_BANK_COMBO_IEEE0 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_SERDES_DIGITAL ; 
 int /*<<< orphan*/  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1 ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_FIBER_MODE ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_INVERT_SIGNAL_DETECT ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_MSTR_MODE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  bnx2x_restart_autoneg (struct bnx2x_phy*,struct link_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_initialize_sgmii_process(struct bnx2x_phy *phy,
					   struct link_params *params,
					   struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u16 control1;

	/* In SGMII mode, the unicore is always slave */

	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1,
			  &control1);
	control1 |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_INVERT_SIGNAL_DETECT;
	/* Set sgmii mode (and not fiber) */
	control1 &= ~(MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_FIBER_MODE |
		      MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET |
		      MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_MSTR_MODE);
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1,
			  control1);

	/* If forced speed */
	if (!(vars->line_speed == SPEED_AUTO_NEG)) {
		/* Set speed, disable autoneg */
		u16 mii_control;

		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  &mii_control);
		mii_control &= ~(MDIO_COMBO_IEEO_MII_CONTROL_AN_EN |
				 MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_MASK|
				 MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX);

		switch (vars->line_speed) {
		case SPEED_100:
			mii_control |=
				MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_100;
			break;
		case SPEED_1000:
			mii_control |=
				MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_1000;
			break;
		case SPEED_10:
			/* There is nothing to set for 10M */
			break;
		default:
			/* Invalid speed for SGMII */
			DP(NETIF_MSG_LINK, "Invalid line_speed 0x%x\n",
				  vars->line_speed);
			break;
		}

		/* Setting the full duplex */
		if (phy->req_duplex == DUPLEX_FULL)
			mii_control |=
				MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX;
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  mii_control);

	} else { /* AN mode */
		/* Enable and restart AN */
		bnx2x_restart_autoneg(phy, params, 0);
	}
}