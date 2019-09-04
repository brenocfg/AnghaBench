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
struct link_vars {int line_speed; scalar_t__ duplex; int link_status; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int flags; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int FLAGS_EEE ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_100T4_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10THD_CAPABLE ; 
 int LINK_STATUS_PARALLEL_DETECTION_USED ; 
 int MDIO_REG_GPHY_AUX_STATUS ; 
 int MDIO_REG_INTR_STATUS ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 int /*<<< orphan*/  bnx2x_cl22_read (struct bnx2x*,struct bnx2x_phy*,int,int*) ; 
 int /*<<< orphan*/  bnx2x_eee_an_resolve (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 scalar_t__ bnx2x_eee_has_cap (struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_ext_phy_resolve_fc (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 

__attribute__((used)) static u8 bnx2x_54618se_read_status(struct bnx2x_phy *phy,
				    struct link_params *params,
				    struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u16 val;
	u8 link_up = 0;
	u16 legacy_status, legacy_speed;

	/* Get speed operation status */
	bnx2x_cl22_read(bp, phy,
			MDIO_REG_GPHY_AUX_STATUS,
			&legacy_status);
	DP(NETIF_MSG_LINK, "54618SE read_status: 0x%x\n", legacy_status);

	/* Read status to clear the PHY interrupt. */
	bnx2x_cl22_read(bp, phy,
			MDIO_REG_INTR_STATUS,
			&val);

	link_up = ((legacy_status & (1<<2)) == (1<<2));

	if (link_up) {
		legacy_speed = (legacy_status & (7<<8));
		if (legacy_speed == (7<<8)) {
			vars->line_speed = SPEED_1000;
			vars->duplex = DUPLEX_FULL;
		} else if (legacy_speed == (6<<8)) {
			vars->line_speed = SPEED_1000;
			vars->duplex = DUPLEX_HALF;
		} else if (legacy_speed == (5<<8)) {
			vars->line_speed = SPEED_100;
			vars->duplex = DUPLEX_FULL;
		}
		/* Omitting 100Base-T4 for now */
		else if (legacy_speed == (3<<8)) {
			vars->line_speed = SPEED_100;
			vars->duplex = DUPLEX_HALF;
		} else if (legacy_speed == (2<<8)) {
			vars->line_speed = SPEED_10;
			vars->duplex = DUPLEX_FULL;
		} else if (legacy_speed == (1<<8)) {
			vars->line_speed = SPEED_10;
			vars->duplex = DUPLEX_HALF;
		} else /* Should not happen */
			vars->line_speed = 0;

		DP(NETIF_MSG_LINK,
		   "Link is up in %dMbps, is_duplex_full= %d\n",
		   vars->line_speed,
		   (vars->duplex == DUPLEX_FULL));

		/* Check legacy speed AN resolution */
		bnx2x_cl22_read(bp, phy,
				0x01,
				&val);
		if (val & (1<<5))
			vars->link_status |=
				LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;
		bnx2x_cl22_read(bp, phy,
				0x06,
				&val);
		if ((val & (1<<0)) == 0)
			vars->link_status |=
				LINK_STATUS_PARALLEL_DETECTION_USED;

		DP(NETIF_MSG_LINK, "BCM54618SE: link speed is %d\n",
			   vars->line_speed);

		bnx2x_ext_phy_resolve_fc(phy, params, vars);

		if (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) {
			/* Report LP advertised speeds */
			bnx2x_cl22_read(bp, phy, 0x5, &val);

			if (val & (1<<5))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_10THD_CAPABLE;
			if (val & (1<<6))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE;
			if (val & (1<<7))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE;
			if (val & (1<<8))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE;
			if (val & (1<<9))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_100T4_CAPABLE;

			bnx2x_cl22_read(bp, phy, 0xa, &val);
			if (val & (1<<10))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE;
			if (val & (1<<11))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;

			if ((phy->flags & FLAGS_EEE) &&
			    bnx2x_eee_has_cap(params))
				bnx2x_eee_an_resolve(phy, params, vars);
		}
	}
	return link_up;
}