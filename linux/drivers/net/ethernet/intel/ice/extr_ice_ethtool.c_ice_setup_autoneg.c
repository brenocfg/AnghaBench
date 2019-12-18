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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int an_info; } ;
struct TYPE_4__ {TYPE_1__ link_info; } ;
struct ice_port_info {TYPE_2__ phy; } ;
struct ice_aqc_set_phy_cfg_data {int /*<<< orphan*/  caps; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  Autoneg ; 
 int EINVAL ; 
 int ICE_AQ_AN_COMPLETED ; 
 int /*<<< orphan*/  ICE_AQ_PHY_ENA_AUTO_LINK_UPDT ; 
 scalar_t__ ethtool_link_ksettings_test_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int
ice_setup_autoneg(struct ice_port_info *p, struct ethtool_link_ksettings *ks,
		  struct ice_aqc_set_phy_cfg_data *config,
		  u8 autoneg_enabled, u8 *autoneg_changed,
		  struct net_device *netdev)
{
	int err = 0;

	*autoneg_changed = 0;

	/* Check autoneg */
	if (autoneg_enabled == AUTONEG_ENABLE) {
		/* If autoneg was not already enabled */
		if (!(p->phy.link_info.an_info & ICE_AQ_AN_COMPLETED)) {
			/* If autoneg is not supported, return error */
			if (!ethtool_link_ksettings_test_link_mode(ks,
								   supported,
								   Autoneg)) {
				netdev_info(netdev, "Autoneg not supported on this phy.\n");
				err = -EINVAL;
			} else {
				/* Autoneg is allowed to change */
				config->caps |= ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;
				*autoneg_changed = 1;
			}
		}
	} else {
		/* If autoneg is currently enabled */
		if (p->phy.link_info.an_info & ICE_AQ_AN_COMPLETED) {
			/* If autoneg is supported 10GBASE_T is the only PHY
			 * that can disable it, so otherwise return error
			 */
			if (ethtool_link_ksettings_test_link_mode(ks,
								  supported,
								  Autoneg)) {
				netdev_info(netdev, "Autoneg cannot be disabled on this phy\n");
				err = -EINVAL;
			} else {
				/* Autoneg is allowed to change */
				config->caps &= ~ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;
				*autoneg_changed = 1;
			}
		}
	}

	return err;
}