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
struct net_device {int /*<<< orphan*/ * phydev; } ;
struct lan743x_adapter {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan743x_phy_close(struct lan743x_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	phy_stop(netdev->phydev);
	phy_disconnect(netdev->phydev);
	netdev->phydev = NULL;
}