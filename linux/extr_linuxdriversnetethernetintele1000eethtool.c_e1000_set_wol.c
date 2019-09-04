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
struct ethtool_wolinfo {int wolopts; } ;
struct e1000_adapter {int flags; int /*<<< orphan*/  wol; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_WUFC_BC ; 
 int /*<<< orphan*/  E1000_WUFC_EX ; 
 int /*<<< orphan*/  E1000_WUFC_LNKC ; 
 int /*<<< orphan*/  E1000_WUFC_MAG ; 
 int /*<<< orphan*/  E1000_WUFC_MC ; 
 int EOPNOTSUPP ; 
 int FLAG_HAS_WOL ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 int /*<<< orphan*/  device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e1000_set_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);

	if (!(adapter->flags & FLAG_HAS_WOL) ||
	    !device_can_wakeup(&adapter->pdev->dev) ||
	    (wol->wolopts & ~(WAKE_UCAST | WAKE_MCAST | WAKE_BCAST |
			      WAKE_MAGIC | WAKE_PHY)))
		return -EOPNOTSUPP;

	/* these settings will always override what we currently have */
	adapter->wol = 0;

	if (wol->wolopts & WAKE_UCAST)
		adapter->wol |= E1000_WUFC_EX;
	if (wol->wolopts & WAKE_MCAST)
		adapter->wol |= E1000_WUFC_MC;
	if (wol->wolopts & WAKE_BCAST)
		adapter->wol |= E1000_WUFC_BC;
	if (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= E1000_WUFC_MAG;
	if (wol->wolopts & WAKE_PHY)
		adapter->wol |= E1000_WUFC_LNKC;

	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	return 0;
}