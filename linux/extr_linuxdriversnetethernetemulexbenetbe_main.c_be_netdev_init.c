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
struct net_device {int hw_features; int features; int vlan_features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  priv_flags; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int BE_IF_FLAGS_RSS ; 
 scalar_t__ BE_MAX_GSO_SIZE ; 
 int /*<<< orphan*/  BE_MAX_MTU ; 
 int /*<<< orphan*/  BE_MIN_MTU ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  be_ethtool_ops ; 
 int be_if_cap_flags (struct be_adapter*) ; 
 int /*<<< orphan*/  be_netdev_ops ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_gso_max_size (struct net_device*,scalar_t__) ; 

__attribute__((used)) static void be_netdev_init(struct net_device *netdev)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	netdev->hw_features |= NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6 |
		NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM |
		NETIF_F_HW_VLAN_CTAG_TX;
	if ((be_if_cap_flags(adapter) & BE_IF_FLAGS_RSS))
		netdev->hw_features |= NETIF_F_RXHASH;

	netdev->features |= netdev->hw_features |
		NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_CTAG_FILTER;

	netdev->vlan_features |= NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6 |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	netdev->flags |= IFF_MULTICAST;

	netif_set_gso_max_size(netdev, BE_MAX_GSO_SIZE - ETH_HLEN);

	netdev->netdev_ops = &be_netdev_ops;

	netdev->ethtool_ops = &be_ethtool_ops;

	/* MTU range: 256 - 9000 */
	netdev->min_mtu = BE_MIN_MTU;
	netdev->max_mtu = BE_MAX_MTU;
}