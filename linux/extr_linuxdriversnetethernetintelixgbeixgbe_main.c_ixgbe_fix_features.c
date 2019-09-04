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
struct net_device {int dummy; } ;
struct ixgbe_adapter {int flags2; scalar_t__ xdp_prog; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int IXGBE_FLAG2_RSC_CAPABLE ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  e_dev_err (char*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t ixgbe_fix_features(struct net_device *netdev,
					    netdev_features_t features)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	/* If Rx checksum is disabled, then RSC/LRO should also be disabled */
	if (!(features & NETIF_F_RXCSUM))
		features &= ~NETIF_F_LRO;

	/* Turn off LRO if not RSC capable */
	if (!(adapter->flags2 & IXGBE_FLAG2_RSC_CAPABLE))
		features &= ~NETIF_F_LRO;

	if (adapter->xdp_prog && (features & NETIF_F_LRO)) {
		e_dev_err("LRO is not supported with XDP\n");
		features &= ~NETIF_F_LRO;
	}

	return features;
}