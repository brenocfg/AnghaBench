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
struct TYPE_2__ {int /*<<< orphan*/  vxn; } ;
struct xgbe_prv_data {int vxlan_features; scalar_t__ vxlan_force_disable; TYPE_1__ hw_feat; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_GSO_UDP_TUNNEL_CSUM ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RX_UDP_TUNNEL_PORT ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t xgbe_fix_features(struct net_device *netdev,
					   netdev_features_t features)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	netdev_features_t vxlan_base, vxlan_mask;

	vxlan_base = NETIF_F_GSO_UDP_TUNNEL | NETIF_F_RX_UDP_TUNNEL_PORT;
	vxlan_mask = vxlan_base | NETIF_F_GSO_UDP_TUNNEL_CSUM;

	pdata->vxlan_features = features & vxlan_mask;

	/* Only fix VXLAN-related features */
	if (!pdata->vxlan_features)
		return features;

	/* If VXLAN isn't supported then clear any features:
	 *   This is needed because NETIF_F_RX_UDP_TUNNEL_PORT gets
	 *   automatically set if ndo_udp_tunnel_add is set.
	 */
	if (!pdata->hw_feat.vxn)
		return features & ~vxlan_mask;

	/* VXLAN CSUM requires VXLAN base */
	if ((features & NETIF_F_GSO_UDP_TUNNEL_CSUM) &&
	    !(features & NETIF_F_GSO_UDP_TUNNEL)) {
		netdev_notice(netdev,
			      "forcing tx udp tunnel support\n");
		features |= NETIF_F_GSO_UDP_TUNNEL;
	}

	/* Can't do one without doing the other */
	if ((features & vxlan_base) != vxlan_base) {
		netdev_notice(netdev,
			      "forcing both tx and rx udp tunnel support\n");
		features |= vxlan_base;
	}

	if (features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) {
		if (!(features & NETIF_F_GSO_UDP_TUNNEL_CSUM)) {
			netdev_notice(netdev,
				      "forcing tx udp tunnel checksumming on\n");
			features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;
		}
	} else {
		if (features & NETIF_F_GSO_UDP_TUNNEL_CSUM) {
			netdev_notice(netdev,
				      "forcing tx udp tunnel checksumming off\n");
			features &= ~NETIF_F_GSO_UDP_TUNNEL_CSUM;
		}
	}

	pdata->vxlan_features = features & vxlan_mask;

	/* Adjust UDP Tunnel based on current state */
	if (pdata->vxlan_force_disable) {
		netdev_notice(netdev,
			      "VXLAN acceleration disabled, turning off udp tunnel features\n");
		features &= ~vxlan_mask;
	}

	return features;
}