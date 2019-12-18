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
struct xgbe_prv_data {int vxlan_offloads_set; int vxlan_features; struct net_device* netdev; } ;
struct net_device {int hw_enc_features; int features; } ;

/* Variables and functions */
 int NETIF_F_GRO ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 

__attribute__((used)) static void xgbe_enable_vxlan_offloads(struct xgbe_prv_data *pdata)
{
	struct net_device *netdev = pdata->netdev;

	if (pdata->vxlan_offloads_set)
		return;

	netdev_info(netdev, "enabling VXLAN offloads\n");

	netdev->hw_enc_features |= NETIF_F_SG |
				   NETIF_F_IP_CSUM |
				   NETIF_F_IPV6_CSUM |
				   NETIF_F_RXCSUM |
				   NETIF_F_TSO |
				   NETIF_F_TSO6 |
				   NETIF_F_GRO |
				   pdata->vxlan_features;

	netdev->features |= pdata->vxlan_features;

	pdata->vxlan_offloads_set = 1;
}