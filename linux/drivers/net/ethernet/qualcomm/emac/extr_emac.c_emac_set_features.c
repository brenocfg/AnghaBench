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
struct net_device {int features; } ;
struct emac_adapter {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int emac_reinit_locked (struct emac_adapter*) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int emac_set_features(struct net_device *netdev,
			     netdev_features_t features)
{
	netdev_features_t changed = features ^ netdev->features;
	struct emac_adapter *adpt = netdev_priv(netdev);

	/* We only need to reprogram the hardware if the VLAN tag features
	 * have changed, and if it's already running.
	 */
	if (!(changed & (NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX)))
		return 0;

	if (!netif_running(netdev))
		return 0;

	/* emac_mac_mode_config() uses netdev->features to configure the EMAC,
	 * so make sure it's set first.
	 */
	netdev->features = features;

	return emac_reinit_locked(adpt);
}