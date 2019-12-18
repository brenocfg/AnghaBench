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
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;
struct atl1_adapter {int wol; } ;

/* Variables and functions */
 int ATLX_WUFC_MAG ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void atl1_get_wol(struct net_device *netdev,
	struct ethtool_wolinfo *wol)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);

	wol->supported = WAKE_MAGIC;
	wol->wolopts = 0;
	if (adapter->wol & ATLX_WUFC_MAG)
		wol->wolopts |= WAKE_MAGIC;
}