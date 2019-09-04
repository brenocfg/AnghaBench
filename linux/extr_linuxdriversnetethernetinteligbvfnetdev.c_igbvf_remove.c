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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct e1000_hw {scalar_t__ flash_address; scalar_t__ hw_addr; } ;
struct igbvf_adapter {TYPE_1__* rx_ring; TYPE_1__* tx_ring; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; struct e1000_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IGBVF_DOWN ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  igbvf_reset_interrupt_capability (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void igbvf_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	/* The watchdog timer may be rescheduled, so explicitly
	 * disable it from being rescheduled.
	 */
	set_bit(__IGBVF_DOWN, &adapter->state);
	del_timer_sync(&adapter->watchdog_timer);

	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->watchdog_task);

	unregister_netdev(netdev);

	igbvf_reset_interrupt_capability(adapter);

	/* it is important to delete the NAPI struct prior to freeing the
	 * Rx ring so that you do not end up with null pointer refs
	 */
	netif_napi_del(&adapter->rx_ring->napi);
	kfree(adapter->tx_ring);
	kfree(adapter->rx_ring);

	iounmap(hw->hw_addr);
	if (hw->flash_address)
		iounmap(hw->flash_address);
	pci_release_regions(pdev);

	free_netdev(netdev);

	pci_disable_device(pdev);
}