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
struct netxen_adapter {int /*<<< orphan*/  tx_timeout_task; int /*<<< orphan*/  state; } ;
struct net_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NX_RESETTING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netxen_tx_timeout(struct net_device *netdev)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);

	if (test_bit(__NX_RESETTING, &adapter->state))
		return;

	dev_err(&netdev->dev, "transmit timeout, resetting.\n");
	schedule_work(&adapter->tx_timeout_task);
}