#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  phydev; } ;
struct mv643xx_eth_private {struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_1000baseT_Half ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Half ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static int
mv643xx_eth_get_link_ksettings_phy(struct mv643xx_eth_private *mp,
				   struct ethtool_link_ksettings *cmd)
{
	struct net_device *dev = mp->dev;
	u32 supported, advertising;

	phy_ethtool_ksettings_get(dev->phydev, cmd);

	/*
	 * The MAC does not support 1000baseT_Half.
	 */
	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);
	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);
	supported &= ~SUPPORTED_1000baseT_Half;
	advertising &= ~ADVERTISED_1000baseT_Half;
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}