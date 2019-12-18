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
typedef  scalar_t__ u32 ;
struct link_config {int supported; scalar_t__ autoneg; scalar_t__ advertising; int /*<<< orphan*/  requested_duplex; scalar_t__ requested_speed; } ;
struct port_info {int /*<<< orphan*/  mac; int /*<<< orphan*/  phy; struct link_config link_config; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ autoneg; scalar_t__ speed; int /*<<< orphan*/  duplex; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 scalar_t__ ADVERTISED_Autoneg ; 
 scalar_t__ ADVERTISED_MASK ; 
 scalar_t__ AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_INVALID ; 
 int EINVAL ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_INVALID ; 
 int SUPPORTED_Autoneg ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int speed_duplex_to_caps (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_link_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct link_config*) ; 

__attribute__((used)) static int set_link_ksettings(struct net_device *dev,
			      const struct ethtool_link_ksettings *cmd)
{
	struct port_info *p = netdev_priv(dev);
	struct link_config *lc = &p->link_config;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	if (!(lc->supported & SUPPORTED_Autoneg)) {
		/*
		 * PHY offers a single speed/duplex.  See if that's what's
		 * being requested.
		 */
		if (cmd->base.autoneg == AUTONEG_DISABLE) {
			u32 speed = cmd->base.speed;
			int cap = speed_duplex_to_caps(speed, cmd->base.duplex);
			if (lc->supported & cap)
				return 0;
		}
		return -EINVAL;
	}

	if (cmd->base.autoneg == AUTONEG_DISABLE) {
		u32 speed = cmd->base.speed;
		int cap = speed_duplex_to_caps(speed, cmd->base.duplex);

		if (!(lc->supported & cap) || (speed == SPEED_1000))
			return -EINVAL;
		lc->requested_speed = speed;
		lc->requested_duplex = cmd->base.duplex;
		lc->advertising = 0;
	} else {
		advertising &= ADVERTISED_MASK;
		advertising &= lc->supported;
		if (!advertising)
			return -EINVAL;
		lc->requested_speed = SPEED_INVALID;
		lc->requested_duplex = DUPLEX_INVALID;
		lc->advertising = advertising | ADVERTISED_Autoneg;
	}
	lc->autoneg = cmd->base.autoneg;
	if (netif_running(dev))
		t3_link_start(&p->phy, &p->mac, lc);
	return 0;
}