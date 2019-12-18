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
struct net_device {int features; int hw_features; int hw_enc_features; int /*<<< orphan*/  priv_flags; } ;
struct ionic_lif {int hw_features; struct net_device* netdev; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int IONIC_ETH_HW_RX_CSUM ; 
 int IONIC_ETH_HW_RX_HASH ; 
 int IONIC_ETH_HW_TSO ; 
 int IONIC_ETH_HW_TSO_ECN ; 
 int IONIC_ETH_HW_TSO_GRE ; 
 int IONIC_ETH_HW_TSO_GRE_CSUM ; 
 int IONIC_ETH_HW_TSO_IPV6 ; 
 int IONIC_ETH_HW_TSO_IPXIP4 ; 
 int IONIC_ETH_HW_TSO_IPXIP6 ; 
 int IONIC_ETH_HW_TSO_UDP ; 
 int IONIC_ETH_HW_TSO_UDP_CSUM ; 
 int IONIC_ETH_HW_TX_CSUM ; 
 int IONIC_ETH_HW_TX_SG ; 
 int IONIC_ETH_HW_VLAN_RX_FILTER ; 
 int IONIC_ETH_HW_VLAN_RX_STRIP ; 
 int IONIC_ETH_HW_VLAN_TX_TAG ; 
 int NETIF_F_GSO_GRE ; 
 int NETIF_F_GSO_GRE_CSUM ; 
 int NETIF_F_GSO_IPXIP4 ; 
 int NETIF_F_GSO_IPXIP6 ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_GSO_UDP_TUNNEL_CSUM ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int NETIF_F_TSO_ECN ; 
 int ionic_set_nic_features (struct ionic_lif*,int) ; 

__attribute__((used)) static int ionic_init_nic_features(struct ionic_lif *lif)
{
	struct net_device *netdev = lif->netdev;
	netdev_features_t features;
	int err;

	/* set up what we expect to support by default */
	features = NETIF_F_HW_VLAN_CTAG_TX |
		   NETIF_F_HW_VLAN_CTAG_RX |
		   NETIF_F_HW_VLAN_CTAG_FILTER |
		   NETIF_F_RXHASH |
		   NETIF_F_SG |
		   NETIF_F_HW_CSUM |
		   NETIF_F_RXCSUM |
		   NETIF_F_TSO |
		   NETIF_F_TSO6 |
		   NETIF_F_TSO_ECN;

	err = ionic_set_nic_features(lif, features);
	if (err)
		return err;

	/* tell the netdev what we actually can support */
	netdev->features |= NETIF_F_HIGHDMA;

	if (lif->hw_features & IONIC_ETH_HW_VLAN_TX_TAG)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX;
	if (lif->hw_features & IONIC_ETH_HW_VLAN_RX_STRIP)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_RX;
	if (lif->hw_features & IONIC_ETH_HW_VLAN_RX_FILTER)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	if (lif->hw_features & IONIC_ETH_HW_RX_HASH)
		netdev->hw_features |= NETIF_F_RXHASH;
	if (lif->hw_features & IONIC_ETH_HW_TX_SG)
		netdev->hw_features |= NETIF_F_SG;

	if (lif->hw_features & IONIC_ETH_HW_TX_CSUM)
		netdev->hw_enc_features |= NETIF_F_HW_CSUM;
	if (lif->hw_features & IONIC_ETH_HW_RX_CSUM)
		netdev->hw_enc_features |= NETIF_F_RXCSUM;
	if (lif->hw_features & IONIC_ETH_HW_TSO)
		netdev->hw_enc_features |= NETIF_F_TSO;
	if (lif->hw_features & IONIC_ETH_HW_TSO_IPV6)
		netdev->hw_enc_features |= NETIF_F_TSO6;
	if (lif->hw_features & IONIC_ETH_HW_TSO_ECN)
		netdev->hw_enc_features |= NETIF_F_TSO_ECN;
	if (lif->hw_features & IONIC_ETH_HW_TSO_GRE)
		netdev->hw_enc_features |= NETIF_F_GSO_GRE;
	if (lif->hw_features & IONIC_ETH_HW_TSO_GRE_CSUM)
		netdev->hw_enc_features |= NETIF_F_GSO_GRE_CSUM;
	if (lif->hw_features & IONIC_ETH_HW_TSO_IPXIP4)
		netdev->hw_enc_features |= NETIF_F_GSO_IPXIP4;
	if (lif->hw_features & IONIC_ETH_HW_TSO_IPXIP6)
		netdev->hw_enc_features |= NETIF_F_GSO_IPXIP6;
	if (lif->hw_features & IONIC_ETH_HW_TSO_UDP)
		netdev->hw_enc_features |= NETIF_F_GSO_UDP_TUNNEL;
	if (lif->hw_features & IONIC_ETH_HW_TSO_UDP_CSUM)
		netdev->hw_enc_features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;

	netdev->hw_features |= netdev->hw_enc_features;
	netdev->features |= netdev->hw_features;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	return 0;
}