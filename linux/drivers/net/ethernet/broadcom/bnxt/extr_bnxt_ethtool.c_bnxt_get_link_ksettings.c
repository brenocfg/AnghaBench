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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_link_settings {int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  speed; void* duplex; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {struct ethtool_link_settings base; } ;
struct bnxt_link_info {scalar_t__ phy_link_status; int duplex; int req_duplex; scalar_t__ media_type; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  req_link_speed; int /*<<< orphan*/  link_speed; scalar_t__ autoneg; } ;
struct bnxt {int /*<<< orphan*/  link_lock; struct bnxt_link_info link_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  Autoneg ; 
 int BNXT_LINK_DUPLEX_FULL ; 
 scalar_t__ BNXT_LINK_LINK ; 
 void* DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 void* DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  FIBRE ; 
 int /*<<< orphan*/  PORT_DA ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_NONE ; 
 scalar_t__ PORT_PHY_QCFG_RESP_MEDIA_TYPE_DAC ; 
 scalar_t__ PORT_PHY_QCFG_RESP_MEDIA_TYPE_FIBRE ; 
 scalar_t__ PORT_PHY_QCFG_RESP_MEDIA_TYPE_TP ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  TP ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  bnxt_fw_to_ethtool_advertised_spds (struct bnxt_link_info*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  bnxt_fw_to_ethtool_lp_adv (struct bnxt_link_info*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  bnxt_fw_to_ethtool_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_fw_to_ethtool_support_spds (struct bnxt_link_info*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_zero_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int bnxt_get_link_ksettings(struct net_device *dev,
				   struct ethtool_link_ksettings *lk_ksettings)
{
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_link_info *link_info = &bp->link_info;
	struct ethtool_link_settings *base = &lk_ksettings->base;
	u32 ethtool_speed;

	ethtool_link_ksettings_zero_link_mode(lk_ksettings, supported);
	mutex_lock(&bp->link_lock);
	bnxt_fw_to_ethtool_support_spds(link_info, lk_ksettings);

	ethtool_link_ksettings_zero_link_mode(lk_ksettings, advertising);
	if (link_info->autoneg) {
		bnxt_fw_to_ethtool_advertised_spds(link_info, lk_ksettings);
		ethtool_link_ksettings_add_link_mode(lk_ksettings,
						     advertising, Autoneg);
		base->autoneg = AUTONEG_ENABLE;
		if (link_info->phy_link_status == BNXT_LINK_LINK)
			bnxt_fw_to_ethtool_lp_adv(link_info, lk_ksettings);
		ethtool_speed = bnxt_fw_to_ethtool_speed(link_info->link_speed);
		if (!netif_carrier_ok(dev))
			base->duplex = DUPLEX_UNKNOWN;
		else if (link_info->duplex & BNXT_LINK_DUPLEX_FULL)
			base->duplex = DUPLEX_FULL;
		else
			base->duplex = DUPLEX_HALF;
	} else {
		base->autoneg = AUTONEG_DISABLE;
		ethtool_speed =
			bnxt_fw_to_ethtool_speed(link_info->req_link_speed);
		base->duplex = DUPLEX_HALF;
		if (link_info->req_duplex == BNXT_LINK_DUPLEX_FULL)
			base->duplex = DUPLEX_FULL;
	}
	base->speed = ethtool_speed;

	base->port = PORT_NONE;
	if (link_info->media_type == PORT_PHY_QCFG_RESP_MEDIA_TYPE_TP) {
		base->port = PORT_TP;
		ethtool_link_ksettings_add_link_mode(lk_ksettings, supported,
						     TP);
		ethtool_link_ksettings_add_link_mode(lk_ksettings, advertising,
						     TP);
	} else {
		ethtool_link_ksettings_add_link_mode(lk_ksettings, supported,
						     FIBRE);
		ethtool_link_ksettings_add_link_mode(lk_ksettings, advertising,
						     FIBRE);

		if (link_info->media_type == PORT_PHY_QCFG_RESP_MEDIA_TYPE_DAC)
			base->port = PORT_DA;
		else if (link_info->media_type ==
			 PORT_PHY_QCFG_RESP_MEDIA_TYPE_FIBRE)
			base->port = PORT_FIBRE;
	}
	base->phy_address = link_info->phy_addr;
	mutex_unlock(&bp->link_lock);

	return 0;
}