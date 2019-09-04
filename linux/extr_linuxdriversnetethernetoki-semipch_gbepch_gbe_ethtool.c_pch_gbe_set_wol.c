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
struct pch_gbe_adapter {int /*<<< orphan*/  wake_up_evt; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PCH_GBE_WLC_BR ; 
 int /*<<< orphan*/  PCH_GBE_WLC_IND ; 
 int /*<<< orphan*/  PCH_GBE_WLC_MLT ; 
 int /*<<< orphan*/  PCH_GBE_WLC_MP ; 
 int WAKE_ARP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MAGICSECURE ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int pch_gbe_set_wol(struct net_device *netdev,
				struct ethtool_wolinfo *wol)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);

	if ((wol->wolopts & (WAKE_PHY | WAKE_ARP | WAKE_MAGICSECURE)))
		return -EOPNOTSUPP;
	/* these settings will always override what we currently have */
	adapter->wake_up_evt = 0;

	if ((wol->wolopts & WAKE_UCAST))
		adapter->wake_up_evt |= PCH_GBE_WLC_IND;
	if ((wol->wolopts & WAKE_MCAST))
		adapter->wake_up_evt |= PCH_GBE_WLC_MLT;
	if ((wol->wolopts & WAKE_BCAST))
		adapter->wake_up_evt |= PCH_GBE_WLC_BR;
	if ((wol->wolopts & WAKE_MAGIC))
		adapter->wake_up_evt |= PCH_GBE_WLC_MP;
	return 0;
}