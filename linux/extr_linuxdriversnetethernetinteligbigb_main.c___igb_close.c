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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct igb_adapter {int /*<<< orphan*/  state; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IGB_RESETTING ; 
 int /*<<< orphan*/  igb_down (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_free_all_rx_resources (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_free_all_tx_resources (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_free_irq (struct igb_adapter*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __igb_close(struct net_device *netdev, bool suspending)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct pci_dev *pdev = adapter->pdev;

	WARN_ON(test_bit(__IGB_RESETTING, &adapter->state));

	if (!suspending)
		pm_runtime_get_sync(&pdev->dev);

	igb_down(adapter);
	igb_free_irq(adapter);

	igb_free_all_tx_resources(adapter);
	igb_free_all_rx_resources(adapter);

	if (!suspending)
		pm_runtime_put_sync(&pdev->dev);
	return 0;
}