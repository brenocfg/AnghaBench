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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct netdev_private {int an_enable; int speed; int full_duplex; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int speed; scalar_t__ autoneg; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int EINVAL ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  mii_set_media (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int rio_set_link_ksettings(struct net_device *dev,
				  const struct ethtool_link_ksettings *cmd)
{
	struct netdev_private *np = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	u8 duplex = cmd->base.duplex;

	netif_carrier_off(dev);
	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		if (np->an_enable) {
			return 0;
		} else {
			np->an_enable = 1;
			mii_set_media(dev);
			return 0;
		}
	} else {
		np->an_enable = 0;
		if (np->speed == 1000) {
			speed = SPEED_100;
			duplex = DUPLEX_FULL;
			printk("Warning!! Can't disable Auto negotiation in 1000Mbps, change to Manual 100Mbps, Full duplex.\n");
		}
		switch (speed) {
		case SPEED_10:
			np->speed = 10;
			np->full_duplex = (duplex == DUPLEX_FULL);
			break;
		case SPEED_100:
			np->speed = 100;
			np->full_duplex = (duplex == DUPLEX_FULL);
			break;
		case SPEED_1000: /* not supported */
		default:
			return -EINVAL;
		}
		mii_set_media(dev);
	}
	return 0;
}