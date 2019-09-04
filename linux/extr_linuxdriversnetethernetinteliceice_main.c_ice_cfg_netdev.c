#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int hw_features; int features; int hw_enc_features; int vlan_features; int watchdog_timeo; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * perm_addr; int /*<<< orphan*/ * dev_addr; } ;
struct ice_vsi {scalar_t__ type; TYPE_4__* port_info; TYPE_2__* back; struct net_device* netdev; int /*<<< orphan*/  alloc_rxq; int /*<<< orphan*/  alloc_txq; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
typedef  int netdev_features_t ;
struct TYPE_7__ {int /*<<< orphan*/ * perm_addr; } ;
struct TYPE_8__ {TYPE_3__ mac; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int HZ ; 
 int /*<<< orphan*/  ICE_MAX_MTU ; 
 scalar_t__ ICE_VSI_PF ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev_mqs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_netdev_ops ; 
 int /*<<< orphan*/  ice_set_ethtool_ops (struct net_device*) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ice_cfg_netdev(struct ice_vsi *vsi)
{
	netdev_features_t csumo_features;
	netdev_features_t vlano_features;
	netdev_features_t dflt_features;
	netdev_features_t tso_features;
	struct ice_netdev_priv *np;
	struct net_device *netdev;
	u8 mac_addr[ETH_ALEN];

	netdev = alloc_etherdev_mqs(sizeof(struct ice_netdev_priv),
				    vsi->alloc_txq, vsi->alloc_rxq);
	if (!netdev)
		return -ENOMEM;

	vsi->netdev = netdev;
	np = netdev_priv(netdev);
	np->vsi = vsi;

	dflt_features = NETIF_F_SG	|
			NETIF_F_HIGHDMA	|
			NETIF_F_RXHASH;

	csumo_features = NETIF_F_RXCSUM	  |
			 NETIF_F_IP_CSUM  |
			 NETIF_F_IPV6_CSUM;

	vlano_features = NETIF_F_HW_VLAN_CTAG_FILTER |
			 NETIF_F_HW_VLAN_CTAG_TX     |
			 NETIF_F_HW_VLAN_CTAG_RX;

	tso_features = NETIF_F_TSO;

	/* set features that user can change */
	netdev->hw_features = dflt_features | csumo_features |
			      vlano_features | tso_features;

	/* enable features */
	netdev->features |= netdev->hw_features;
	/* encap and VLAN devices inherit default, csumo and tso features */
	netdev->hw_enc_features |= dflt_features | csumo_features |
				   tso_features;
	netdev->vlan_features |= dflt_features | csumo_features |
				 tso_features;

	if (vsi->type == ICE_VSI_PF) {
		SET_NETDEV_DEV(netdev, &vsi->back->pdev->dev);
		ether_addr_copy(mac_addr, vsi->port_info->mac.perm_addr);

		ether_addr_copy(netdev->dev_addr, mac_addr);
		ether_addr_copy(netdev->perm_addr, mac_addr);
	}

	netdev->priv_flags |= IFF_UNICAST_FLT;

	/* assign netdev_ops */
	netdev->netdev_ops = &ice_netdev_ops;

	/* setup watchdog timeout value to be 5 second */
	netdev->watchdog_timeo = 5 * HZ;

	ice_set_ethtool_ops(netdev);

	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = ICE_MAX_MTU;

	return 0;
}