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
struct rtl8169_private {scalar_t__ mac_version; } ;
struct net_device {scalar_t__ mtu; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 scalar_t__ JUMBO_1K ; 
 int /*<<< orphan*/  NETIF_F_ALL_TSO ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 scalar_t__ RTL_GIGA_MAC_VER_06 ; 
 scalar_t__ TD_MSS_MAX ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t rtl8169_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (dev->mtu > TD_MSS_MAX)
		features &= ~NETIF_F_ALL_TSO;

	if (dev->mtu > JUMBO_1K &&
	    tp->mac_version > RTL_GIGA_MAC_VER_06)
		features &= ~NETIF_F_IP_CSUM;

	return features;
}