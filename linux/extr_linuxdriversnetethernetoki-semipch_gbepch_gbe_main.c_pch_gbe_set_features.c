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
struct pch_gbe_adapter {int dummy; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_reinit_locked (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_reset (struct pch_gbe_adapter*) ; 

__attribute__((used)) static int pch_gbe_set_features(struct net_device *netdev,
	netdev_features_t features)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	if (!(changed & NETIF_F_RXCSUM))
		return 0;

	if (netif_running(netdev))
		pch_gbe_reinit_locked(adapter);
	else
		pch_gbe_reset(adapter);

	return 0;
}