#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ flash_address; TYPE_1__ mac; scalar_t__ hw_addr; } ;
struct e1000_adapter {int flags; TYPE_2__ hw; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  state; int /*<<< orphan*/ * tx_hwtstamp_skb; int /*<<< orphan*/  tx_hwtstamp_work; int /*<<< orphan*/  e1000_workqueue; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  print_hang_task; int /*<<< orphan*/  update_phy_task; int /*<<< orphan*/  downshift_task; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  phy_info_timer; } ;

/* Variables and functions */
 int FLAG_HAS_HW_TIMESTAMP ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_consume_skb_any (int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_pch_spt ; 
 int /*<<< orphan*/  e1000e_ptp_remove (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_release_hw_control (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_reset_interrupt_capability (struct e1000_adapter*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ pci_dev_run_wake (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void e1000_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct e1000_adapter *adapter = netdev_priv(netdev);
	bool down = test_bit(__E1000_DOWN, &adapter->state);

	e1000e_ptp_remove(adapter);

	/* The timers may be rescheduled, so explicitly disable them
	 * from being rescheduled.
	 */
	if (!down)
		set_bit(__E1000_DOWN, &adapter->state);
	del_timer_sync(&adapter->phy_info_timer);

	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->downshift_task);
	cancel_work_sync(&adapter->update_phy_task);
	cancel_work_sync(&adapter->print_hang_task);

	cancel_delayed_work(&adapter->watchdog_task);
	flush_workqueue(adapter->e1000_workqueue);
	destroy_workqueue(adapter->e1000_workqueue);

	if (adapter->flags & FLAG_HAS_HW_TIMESTAMP) {
		cancel_work_sync(&adapter->tx_hwtstamp_work);
		if (adapter->tx_hwtstamp_skb) {
			dev_consume_skb_any(adapter->tx_hwtstamp_skb);
			adapter->tx_hwtstamp_skb = NULL;
		}
	}

	/* Don't lie to e1000_close() down the road. */
	if (!down)
		clear_bit(__E1000_DOWN, &adapter->state);
	unregister_netdev(netdev);

	if (pci_dev_run_wake(pdev))
		pm_runtime_get_noresume(&pdev->dev);

	/* Release control of h/w to f/w.  If f/w is AMT enabled, this
	 * would have already happened in close and is redundant.
	 */
	e1000e_release_hw_control(adapter);

	e1000e_reset_interrupt_capability(adapter);
	kfree(adapter->tx_ring);
	kfree(adapter->rx_ring);

	iounmap(adapter->hw.hw_addr);
	if ((adapter->hw.flash_address) &&
	    (adapter->hw.mac.type < e1000_pch_spt))
		iounmap(adapter->hw.flash_address);
	pci_release_mem_regions(pdev);

	free_netdev(netdev);

	/* AER disable */
	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
}