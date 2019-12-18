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
typedef  int /*<<< orphan*/  u32 ;
struct r8152 {int /*<<< orphan*/  intf; int /*<<< orphan*/  control; int /*<<< orphan*/  advertising; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10baseT_Half_BIT ; 
 int /*<<< orphan*/  RTL_ADVERTISED_1000_FULL ; 
 int /*<<< orphan*/  RTL_ADVERTISED_1000_HALF ; 
 int /*<<< orphan*/  RTL_ADVERTISED_100_FULL ; 
 int /*<<< orphan*/  RTL_ADVERTISED_100_HALF ; 
 int /*<<< orphan*/  RTL_ADVERTISED_10_FULL ; 
 int /*<<< orphan*/  RTL_ADVERTISED_10_HALF ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int rtl8152_set_speed (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_set_link_ksettings(struct net_device *dev,
				      const struct ethtool_link_ksettings *cmd)
{
	struct r8152 *tp = netdev_priv(dev);
	u32 advertising = 0;
	int ret;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	if (test_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_10_HALF;

	if (test_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_10_FULL;

	if (test_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_100_HALF;

	if (test_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_100_FULL;

	if (test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_1000_HALF;

	if (test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_1000_FULL;

	mutex_lock(&tp->control);

	ret = rtl8152_set_speed(tp, cmd->base.autoneg, cmd->base.speed,
				cmd->base.duplex, advertising);
	if (!ret) {
		tp->autoneg = cmd->base.autoneg;
		tp->speed = cmd->base.speed;
		tp->duplex = cmd->base.duplex;
		tp->advertising = advertising;
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}