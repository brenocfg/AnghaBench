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
typedef  int u16 ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ req_line_speed; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int MDIO_AER_BLOCK_AER_REG ; 
 int MDIO_CL73_IEEEB0_CL73_AN_CONTROL ; 
 int MDIO_COMBO_IEEE0_MII_CONTROL ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_LOOPBACK ; 
 scalar_t__ MDIO_REG_BANK_AER_BLOCK ; 
 scalar_t__ MDIO_REG_BANK_CL73_IEEEB0 ; 
 scalar_t__ MDIO_REG_BANK_COMBO_IEEE0 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ NIG_REG_XGXS0_CTRL_MD_DEVAD ; 
 int REG_RD (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  bnx2x_set_aer_mmd (struct link_params*,struct bnx2x_phy*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void bnx2x_set_xgxs_loopback(struct bnx2x_phy *phy,
				    struct link_params *params)
{
	u8 port = params->port;
	struct bnx2x *bp = params->bp;

	if (phy->req_line_speed != SPEED_1000) {
		u32 md_devad = 0;

		DP(NETIF_MSG_LINK, "XGXS 10G loopback enable\n");

		if (!CHIP_IS_E3(bp)) {
			/* Change the uni_phy_addr in the nig */
			md_devad = REG_RD(bp, (NIG_REG_XGXS0_CTRL_MD_DEVAD +
					       port*0x18));

			REG_WR(bp, NIG_REG_XGXS0_CTRL_MD_DEVAD + port*0x18,
			       0x5);
		}

		bnx2x_cl45_write(bp, phy,
				 5,
				 (MDIO_REG_BANK_AER_BLOCK +
				  (MDIO_AER_BLOCK_AER_REG & 0xf)),
				 0x2800);

		bnx2x_cl45_write(bp, phy,
				 5,
				 (MDIO_REG_BANK_CL73_IEEEB0 +
				  (MDIO_CL73_IEEEB0_CL73_AN_CONTROL & 0xf)),
				 0x6041);
		msleep(200);
		/* Set aer mmd back */
		bnx2x_set_aer_mmd(params, phy);

		if (!CHIP_IS_E3(bp)) {
			/* And md_devad */
			REG_WR(bp, NIG_REG_XGXS0_CTRL_MD_DEVAD + port*0x18,
			       md_devad);
		}
	} else {
		u16 mii_ctrl;
		DP(NETIF_MSG_LINK, "XGXS 1G loopback enable\n");
		bnx2x_cl45_read(bp, phy, 5,
				(MDIO_REG_BANK_COMBO_IEEE0 +
				(MDIO_COMBO_IEEE0_MII_CONTROL & 0xf)),
				&mii_ctrl);
		bnx2x_cl45_write(bp, phy, 5,
				 (MDIO_REG_BANK_COMBO_IEEE0 +
				 (MDIO_COMBO_IEEE0_MII_CONTROL & 0xf)),
				 mii_ctrl |
				 MDIO_COMBO_IEEO_MII_CONTROL_LOOPBACK);
	}
}