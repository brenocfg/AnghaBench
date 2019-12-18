#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct uli526x_board_info {scalar_t__ op_mode; int media_mode; scalar_t__ link_failed; int /*<<< orphan*/  phy_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_MII ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 scalar_t__ ULI526X_100MFD ; 
 scalar_t__ ULI526X_100MHF ; 
 scalar_t__ ULI526X_10MFD ; 
 int ULI526X_AUTO ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ULi_ethtool_get_link_ksettings(struct uli526x_board_info *db,
			       struct ethtool_link_ksettings *cmd)
{
	u32 supported, advertising;

	supported = (SUPPORTED_10baseT_Half |
	                   SUPPORTED_10baseT_Full |
	                   SUPPORTED_100baseT_Half |
	                   SUPPORTED_100baseT_Full |
	                   SUPPORTED_Autoneg |
	                   SUPPORTED_MII);

	advertising = (ADVERTISED_10baseT_Half |
	                   ADVERTISED_10baseT_Full |
	                   ADVERTISED_100baseT_Half |
	                   ADVERTISED_100baseT_Full |
	                   ADVERTISED_Autoneg |
	                   ADVERTISED_MII);

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	cmd->base.port = PORT_MII;
	cmd->base.phy_address = db->phy_addr;

	cmd->base.speed = SPEED_10;
	cmd->base.duplex = DUPLEX_HALF;

	if(db->op_mode==ULI526X_100MHF || db->op_mode==ULI526X_100MFD)
	{
		cmd->base.speed = SPEED_100;
	}
	if(db->op_mode==ULI526X_10MFD || db->op_mode==ULI526X_100MFD)
	{
		cmd->base.duplex = DUPLEX_FULL;
	}
	if(db->link_failed)
	{
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	}

	if (db->media_mode & ULI526X_AUTO)
	{
		cmd->base.autoneg = AUTONEG_ENABLE;
	}
}