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
struct pci_dev {int revision; } ;
struct net_device {int hw_enc_features; int gso_partial_features; int features; int vlan_features; int hw_features; int /*<<< orphan*/  priv_flags; } ;
struct hnae3_handle {int flags; struct pci_dev* pdev; } ;

/* Variables and functions */
 int HNAE3_SUPPORT_VF ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int NETIF_F_GRO ; 
 int NETIF_F_GRO_HW ; 
 int NETIF_F_GSO ; 
 int NETIF_F_GSO_GRE ; 
 int NETIF_F_GSO_GRE_CSUM ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_GSO_UDP_TUNNEL_CSUM ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_NTUPLE ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SCTP_CRC ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int NETIF_F_TSO_MANGLEID ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 

__attribute__((used)) static void hns3_set_default_feature(struct net_device *netdev)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);
	struct pci_dev *pdev = h->pdev;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	netdev->hw_enc_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_GSO |
		NETIF_F_GRO | NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_GSO_GRE |
		NETIF_F_GSO_GRE_CSUM | NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_GSO_UDP_TUNNEL_CSUM | NETIF_F_SCTP_CRC;

	netdev->hw_enc_features |= NETIF_F_TSO_MANGLEID;

	netdev->gso_partial_features |= NETIF_F_GSO_GRE_CSUM;

	netdev->features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_HW_VLAN_CTAG_FILTER |
		NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
		NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_GSO |
		NETIF_F_GRO | NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_GSO_GRE |
		NETIF_F_GSO_GRE_CSUM | NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_GSO_UDP_TUNNEL_CSUM | NETIF_F_SCTP_CRC;

	netdev->vlan_features |=
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM |
		NETIF_F_SG | NETIF_F_GSO | NETIF_F_GRO |
		NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_GSO_GRE |
		NETIF_F_GSO_GRE_CSUM | NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_GSO_UDP_TUNNEL_CSUM | NETIF_F_SCTP_CRC;

	netdev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
		NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_GSO |
		NETIF_F_GRO | NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_GSO_GRE |
		NETIF_F_GSO_GRE_CSUM | NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_GSO_UDP_TUNNEL_CSUM | NETIF_F_SCTP_CRC;

	if (pdev->revision >= 0x21) {
		netdev->hw_features |= NETIF_F_GRO_HW;
		netdev->features |= NETIF_F_GRO_HW;

		if (!(h->flags & HNAE3_SUPPORT_VF)) {
			netdev->hw_features |= NETIF_F_NTUPLE;
			netdev->features |= NETIF_F_NTUPLE;
		}
	}
}