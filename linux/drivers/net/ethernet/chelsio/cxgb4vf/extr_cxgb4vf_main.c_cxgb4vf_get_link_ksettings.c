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
struct TYPE_4__ {int pcaps; int acaps; int lpacaps; scalar_t__ autoneg; int /*<<< orphan*/  speed; } ;
struct port_info {scalar_t__ port_type; scalar_t__ mdio_addr; TYPE_2__ link_cfg; int /*<<< orphan*/  mod_type; } ;
struct net_device {int dummy; } ;
struct ethtool_link_settings {int phy_address; scalar_t__ autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ mdio_support; int /*<<< orphan*/  port; } ;
struct TYPE_3__ {int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; struct ethtool_link_settings base; } ;

/* Variables and functions */
 int /*<<< orphan*/  Autoneg ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 scalar_t__ ETH_MDIO_SUPPORTS_C22 ; 
 scalar_t__ ETH_MDIO_SUPPORTS_C45 ; 
 int FW_PORT_CAP32_ANEG ; 
 scalar_t__ FW_PORT_TYPE_BT_SGMII ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_zero_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_fw_port_mod_type (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_caps_to_lmm (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp_advertising ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  supported ; 
 int /*<<< orphan*/  t4vf_update_port_info (struct port_info*) ; 

__attribute__((used)) static int cxgb4vf_get_link_ksettings(struct net_device *dev,
				  struct ethtool_link_ksettings *link_ksettings)
{
	struct port_info *pi = netdev_priv(dev);
	struct ethtool_link_settings *base = &link_ksettings->base;

	/* For the nonce, the Firmware doesn't send up Port State changes
	 * when the Virtual Interface attached to the Port is down.  So
	 * if it's down, let's grab any changes.
	 */
	if (!netif_running(dev))
		(void)t4vf_update_port_info(pi);

	ethtool_link_ksettings_zero_link_mode(link_ksettings, supported);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, advertising);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, lp_advertising);

	base->port = from_fw_port_mod_type(pi->port_type, pi->mod_type);

	if (pi->mdio_addr >= 0) {
		base->phy_address = pi->mdio_addr;
		base->mdio_support = (pi->port_type == FW_PORT_TYPE_BT_SGMII
				      ? ETH_MDIO_SUPPORTS_C22
				      : ETH_MDIO_SUPPORTS_C45);
	} else {
		base->phy_address = 255;
		base->mdio_support = 0;
	}

	fw_caps_to_lmm(pi->port_type, pi->link_cfg.pcaps,
		       link_ksettings->link_modes.supported);
	fw_caps_to_lmm(pi->port_type, pi->link_cfg.acaps,
		       link_ksettings->link_modes.advertising);
	fw_caps_to_lmm(pi->port_type, pi->link_cfg.lpacaps,
		       link_ksettings->link_modes.lp_advertising);

	if (netif_carrier_ok(dev)) {
		base->speed = pi->link_cfg.speed;
		base->duplex = DUPLEX_FULL;
	} else {
		base->speed = SPEED_UNKNOWN;
		base->duplex = DUPLEX_UNKNOWN;
	}

	base->autoneg = pi->link_cfg.autoneg;
	if (pi->link_cfg.pcaps & FW_PORT_CAP32_ANEG)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Autoneg);
	if (pi->link_cfg.autoneg)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Autoneg);

	return 0;
}