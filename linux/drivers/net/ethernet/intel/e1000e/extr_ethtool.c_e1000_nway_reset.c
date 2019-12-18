#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_3__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  autoneg; } ;
struct TYPE_5__ {TYPE_1__ mac; } ;
struct e1000_adapter {TYPE_2__ hw; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  e1000e_reinit_locked (struct e1000_adapter*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e1000_nway_reset(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);

	if (!netif_running(netdev))
		return -EAGAIN;

	if (!adapter->hw.mac.autoneg)
		return -EINVAL;

	pm_runtime_get_sync(netdev->dev.parent);
	e1000e_reinit_locked(adapter);
	pm_runtime_put_sync(netdev->dev.parent);

	return 0;
}