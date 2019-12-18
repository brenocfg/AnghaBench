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
struct lio {int dev_capability; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 struct lio* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t liquidio_fix_features(struct net_device *netdev,
					       netdev_features_t request)
{
	struct lio *lio = netdev_priv(netdev);

	if ((request & NETIF_F_RXCSUM) &&
	    !(lio->dev_capability & NETIF_F_RXCSUM))
		request &= ~NETIF_F_RXCSUM;

	if ((request & NETIF_F_HW_CSUM) &&
	    !(lio->dev_capability & NETIF_F_HW_CSUM))
		request &= ~NETIF_F_HW_CSUM;

	if ((request & NETIF_F_TSO) && !(lio->dev_capability & NETIF_F_TSO))
		request &= ~NETIF_F_TSO;

	if ((request & NETIF_F_TSO6) && !(lio->dev_capability & NETIF_F_TSO6))
		request &= ~NETIF_F_TSO6;

	if ((request & NETIF_F_LRO) && !(lio->dev_capability & NETIF_F_LRO))
		request &= ~NETIF_F_LRO;

	/*Disable LRO if RXCSUM is off */
	if (!(request & NETIF_F_RXCSUM) && (netdev->features & NETIF_F_LRO) &&
	    (lio->dev_capability & NETIF_F_LRO))
		request &= ~NETIF_F_LRO;

	if ((request & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    !(lio->dev_capability & NETIF_F_HW_VLAN_CTAG_FILTER))
		request &= ~NETIF_F_HW_VLAN_CTAG_FILTER;

	return request;
}