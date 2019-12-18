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
typedef  int u16 ;
struct link_vars {int dummy; } ;
struct link_params {scalar_t__* req_line_speed; scalar_t__ loopback_mode; int num_phys; struct bnx2x_phy* phy; struct bnx2x* bp; } ;
struct bnx2x_phy {int (* read_status ) (struct bnx2x_phy*,struct link_params*,struct link_vars*) ;int /*<<< orphan*/  media_type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ESRCH ; 
 int /*<<< orphan*/  ETH_PHY_DA_TWINAX ; 
 int /*<<< orphan*/  ETH_PHY_SFPP_10G_FIBER ; 
 int /*<<< orphan*/  ETH_PHY_SFP_1G_FIBER ; 
 int /*<<< orphan*/  ETH_PHY_XFP_FIBER ; 
 size_t EXT_PHY1 ; 
 size_t INT_PHY ; 
 size_t LINK_CONFIG_IDX (size_t) ; 
 scalar_t__ LOOPBACK_XGXS ; 
 int /*<<< orphan*/  MDIO_GP_STATUS_TOP_AN_STATUS1 ; 
 int MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS ; 
 int /*<<< orphan*/  MDIO_REG_BANK_GP_STATUS ; 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int MDIO_WC_REG_GP2_STATUS_GP_2_1 ; 
 scalar_t__ SPEED_10000 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int,int*) ; 
 int bnx2x_get_warpcore_lane (struct bnx2x_phy*,struct link_params*) ; 
 int stub1 (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 int stub2 (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 

int bnx2x_test_link(struct link_params *params, struct link_vars *vars,
		    u8 is_serdes)
{
	struct bnx2x *bp = params->bp;
	u16 gp_status = 0, phy_index = 0;
	u8 ext_phy_link_up = 0, serdes_phy_type;
	struct link_vars temp_vars;
	struct bnx2x_phy *int_phy = &params->phy[INT_PHY];

	if (CHIP_IS_E3(bp)) {
		u16 link_up;
		if (params->req_line_speed[LINK_CONFIG_IDX(INT_PHY)]
		    > SPEED_10000) {
			/* Check 20G link */
			bnx2x_cl45_read(bp, int_phy, MDIO_WC_DEVAD,
					1, &link_up);
			bnx2x_cl45_read(bp, int_phy, MDIO_WC_DEVAD,
					1, &link_up);
			link_up &= (1<<2);
		} else {
			/* Check 10G link and below*/
			u8 lane = bnx2x_get_warpcore_lane(int_phy, params);
			bnx2x_cl45_read(bp, int_phy, MDIO_WC_DEVAD,
					MDIO_WC_REG_GP2_STATUS_GP_2_1,
					&gp_status);
			gp_status = ((gp_status >> 8) & 0xf) |
				((gp_status >> 12) & 0xf);
			link_up = gp_status & (1 << lane);
		}
		if (!link_up)
			return -ESRCH;
	} else {
		CL22_RD_OVER_CL45(bp, int_phy,
			  MDIO_REG_BANK_GP_STATUS,
			  MDIO_GP_STATUS_TOP_AN_STATUS1,
			  &gp_status);
		/* Link is up only if both local phy and external phy are up */
		if (!(gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS))
			return -ESRCH;
	}
	/* In XGXS loopback mode, do not check external PHY */
	if (params->loopback_mode == LOOPBACK_XGXS)
		return 0;

	switch (params->num_phys) {
	case 1:
		/* No external PHY */
		return 0;
	case 2:
		ext_phy_link_up = params->phy[EXT_PHY1].read_status(
			&params->phy[EXT_PHY1],
			params, &temp_vars);
		break;
	case 3: /* Dual Media */
		for (phy_index = EXT_PHY1; phy_index < params->num_phys;
		      phy_index++) {
			serdes_phy_type = ((params->phy[phy_index].media_type ==
					    ETH_PHY_SFPP_10G_FIBER) ||
					   (params->phy[phy_index].media_type ==
					    ETH_PHY_SFP_1G_FIBER) ||
					   (params->phy[phy_index].media_type ==
					    ETH_PHY_XFP_FIBER) ||
					   (params->phy[phy_index].media_type ==
					    ETH_PHY_DA_TWINAX));

			if (is_serdes != serdes_phy_type)
				continue;
			if (params->phy[phy_index].read_status) {
				ext_phy_link_up |=
					params->phy[phy_index].read_status(
						&params->phy[phy_index],
						params, &temp_vars);
			}
		}
		break;
	}
	if (ext_phy_link_up)
		return 0;
	return -ESRCH;
}