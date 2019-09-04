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
struct link_vars {int /*<<< orphan*/  line_speed; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int MDIO_PMA_REG_RX_SD ; 
 int /*<<< orphan*/  MDIO_WIS_DEVAD ; 
 int MDIO_WIS_REG_LASI_STATUS ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  bnx2x_ext_phy_resolve_fc (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 

__attribute__((used)) static u8 bnx2x_8705_read_status(struct bnx2x_phy *phy,
				 struct link_params *params,
				 struct link_vars *vars)
{
	u8 link_up = 0;
	u16 val1, rx_sd;
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "read status 8705\n");
	bnx2x_cl45_read(bp, phy,
		      MDIO_WIS_DEVAD, MDIO_WIS_REG_LASI_STATUS, &val1);
	DP(NETIF_MSG_LINK, "8705 LASI status 0x%x\n", val1);

	bnx2x_cl45_read(bp, phy,
		      MDIO_WIS_DEVAD, MDIO_WIS_REG_LASI_STATUS, &val1);
	DP(NETIF_MSG_LINK, "8705 LASI status 0x%x\n", val1);

	bnx2x_cl45_read(bp, phy,
		      MDIO_PMA_DEVAD, MDIO_PMA_REG_RX_SD, &rx_sd);

	bnx2x_cl45_read(bp, phy,
		      MDIO_PMA_DEVAD, 0xc809, &val1);
	bnx2x_cl45_read(bp, phy,
		      MDIO_PMA_DEVAD, 0xc809, &val1);

	DP(NETIF_MSG_LINK, "8705 1.c809 val=0x%x\n", val1);
	link_up = ((rx_sd & 0x1) && (val1 & (1<<9)) && ((val1 & (1<<8)) == 0));
	if (link_up) {
		vars->line_speed = SPEED_10000;
		bnx2x_ext_phy_resolve_fc(phy, params, vars);
	}
	return link_up;
}