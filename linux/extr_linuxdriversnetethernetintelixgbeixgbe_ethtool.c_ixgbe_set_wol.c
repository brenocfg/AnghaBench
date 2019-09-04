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
struct net_device {int dummy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  wol; TYPE_1__* pdev; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IXGBE_WUFC_BC ; 
 int /*<<< orphan*/  IXGBE_WUFC_EX ; 
 int /*<<< orphan*/  IXGBE_WUFC_MAG ; 
 int /*<<< orphan*/  IXGBE_WUFC_MC ; 
 int WAKE_ARP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MAGICSECURE ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_wol_exclusion (struct ixgbe_adapter*,struct ethtool_wolinfo*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_set_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	if (wol->wolopts & (WAKE_PHY | WAKE_ARP | WAKE_MAGICSECURE))
		return -EOPNOTSUPP;

	if (ixgbe_wol_exclusion(adapter, wol))
		return wol->wolopts ? -EOPNOTSUPP : 0;

	adapter->wol = 0;

	if (wol->wolopts & WAKE_UCAST)
		adapter->wol |= IXGBE_WUFC_EX;
	if (wol->wolopts & WAKE_MCAST)
		adapter->wol |= IXGBE_WUFC_MC;
	if (wol->wolopts & WAKE_BCAST)
		adapter->wol |= IXGBE_WUFC_BC;
	if (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= IXGBE_WUFC_MAG;

	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	return 0;
}