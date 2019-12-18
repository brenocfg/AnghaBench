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
struct e1000_adapter {int /*<<< orphan*/  hw; int /*<<< orphan*/  state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int E1000_CHECK_RESET_COUNT ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  __E1000_RESETTING ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  e1000_free_irq (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_disable_pcie_master (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000e_down (struct e1000_adapter*,int) ; 
 int /*<<< orphan*/  e1000e_reset_interrupt_capability (struct e1000_adapter*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int e1000e_pm_freeze(struct device *dev)
{
	struct net_device *netdev = dev_get_drvdata(dev);
	struct e1000_adapter *adapter = netdev_priv(netdev);

	netif_device_detach(netdev);

	if (netif_running(netdev)) {
		int count = E1000_CHECK_RESET_COUNT;

		while (test_bit(__E1000_RESETTING, &adapter->state) && count--)
			usleep_range(10000, 11000);

		WARN_ON(test_bit(__E1000_RESETTING, &adapter->state));

		/* Quiesce the device without resetting the hardware */
		e1000e_down(adapter, false);
		e1000_free_irq(adapter);
	}
	e1000e_reset_interrupt_capability(adapter);

	/* Allow time for pending master requests to run */
	e1000e_disable_pcie_master(&adapter->hw);

	return 0;
}