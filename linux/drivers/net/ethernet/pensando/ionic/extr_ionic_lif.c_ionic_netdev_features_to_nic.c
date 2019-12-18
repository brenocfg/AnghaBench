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
typedef  int /*<<< orphan*/  u64 ;
typedef  int netdev_features_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_ETH_HW_RX_CSUM ; 
 int /*<<< orphan*/  IONIC_ETH_HW_RX_HASH ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TSO ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TSO_ECN ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TSO_GRE ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TSO_GRE_CSUM ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TSO_IPV6 ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TSO_IPXIP4 ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TSO_IPXIP6 ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TSO_UDP ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TSO_UDP_CSUM ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TX_CSUM ; 
 int /*<<< orphan*/  IONIC_ETH_HW_TX_SG ; 
 int /*<<< orphan*/  IONIC_ETH_HW_VLAN_RX_FILTER ; 
 int /*<<< orphan*/  IONIC_ETH_HW_VLAN_RX_STRIP ; 
 int /*<<< orphan*/  IONIC_ETH_HW_VLAN_TX_TAG ; 
 int NETIF_F_GSO_GRE ; 
 int NETIF_F_GSO_GRE_CSUM ; 
 int NETIF_F_GSO_IPXIP4 ; 
 int NETIF_F_GSO_IPXIP6 ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_GSO_UDP_TUNNEL_CSUM ; 
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
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le64 ionic_netdev_features_to_nic(netdev_features_t features)
{
	u64 wanted = 0;

	if (features & NETIF_F_HW_VLAN_CTAG_TX)
		wanted |= IONIC_ETH_HW_VLAN_TX_TAG;
	if (features & NETIF_F_HW_VLAN_CTAG_RX)
		wanted |= IONIC_ETH_HW_VLAN_RX_STRIP;
	if (features & NETIF_F_HW_VLAN_CTAG_FILTER)
		wanted |= IONIC_ETH_HW_VLAN_RX_FILTER;
	if (features & NETIF_F_RXHASH)
		wanted |= IONIC_ETH_HW_RX_HASH;
	if (features & NETIF_F_RXCSUM)
		wanted |= IONIC_ETH_HW_RX_CSUM;
	if (features & NETIF_F_SG)
		wanted |= IONIC_ETH_HW_TX_SG;
	if (features & NETIF_F_HW_CSUM)
		wanted |= IONIC_ETH_HW_TX_CSUM;
	if (features & NETIF_F_TSO)
		wanted |= IONIC_ETH_HW_TSO;
	if (features & NETIF_F_TSO6)
		wanted |= IONIC_ETH_HW_TSO_IPV6;
	if (features & NETIF_F_TSO_ECN)
		wanted |= IONIC_ETH_HW_TSO_ECN;
	if (features & NETIF_F_GSO_GRE)
		wanted |= IONIC_ETH_HW_TSO_GRE;
	if (features & NETIF_F_GSO_GRE_CSUM)
		wanted |= IONIC_ETH_HW_TSO_GRE_CSUM;
	if (features & NETIF_F_GSO_IPXIP4)
		wanted |= IONIC_ETH_HW_TSO_IPXIP4;
	if (features & NETIF_F_GSO_IPXIP6)
		wanted |= IONIC_ETH_HW_TSO_IPXIP6;
	if (features & NETIF_F_GSO_UDP_TUNNEL)
		wanted |= IONIC_ETH_HW_TSO_UDP;
	if (features & NETIF_F_GSO_UDP_TUNNEL_CSUM)
		wanted |= IONIC_ETH_HW_TSO_UDP_CSUM;

	return cpu_to_le64(wanted);
}