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
struct e1000_hw {scalar_t__ flash_address; } ;
struct igb_adapter {int flags; int /*<<< orphan*/  shadow_vfta; int /*<<< orphan*/  mac_table; int /*<<< orphan*/  io_addr; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  phy_info_timer; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_DCA_CTRL ; 
 int /*<<< orphan*/  E1000_DCA_CTRL_DCA_MODE_DISABLE ; 
 int IGB_FLAG_DCA_ENABLED ; 
 int /*<<< orphan*/  __IGB_DOWN ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dca_remove_requester (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  igb_clear_interrupt_scheme (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_disable_sriov (struct pci_dev*) ; 
 int /*<<< orphan*/  igb_ptp_stop (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_release_hw_control (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_remove_i2c (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_sysfs_exit (struct igb_adapter*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	pm_runtime_get_noresume(&pdev->dev);
#ifdef CONFIG_IGB_HWMON
	igb_sysfs_exit(adapter);
#endif
	igb_remove_i2c(adapter);
	igb_ptp_stop(adapter);
	/* The watchdog timer may be rescheduled, so explicitly
	 * disable watchdog from being rescheduled.
	 */
	set_bit(__IGB_DOWN, &adapter->state);
	del_timer_sync(&adapter->watchdog_timer);
	del_timer_sync(&adapter->phy_info_timer);

	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->watchdog_task);

#ifdef CONFIG_IGB_DCA
	if (adapter->flags & IGB_FLAG_DCA_ENABLED) {
		dev_info(&pdev->dev, "DCA disabled\n");
		dca_remove_requester(&pdev->dev);
		adapter->flags &= ~IGB_FLAG_DCA_ENABLED;
		wr32(E1000_DCA_CTRL, E1000_DCA_CTRL_DCA_MODE_DISABLE);
	}
#endif

	/* Release control of h/w to f/w.  If f/w is AMT enabled, this
	 * would have already happened in close and is redundant.
	 */
	igb_release_hw_control(adapter);

#ifdef CONFIG_PCI_IOV
	igb_disable_sriov(pdev);
#endif

	unregister_netdev(netdev);

	igb_clear_interrupt_scheme(adapter);

	pci_iounmap(pdev, adapter->io_addr);
	if (hw->flash_address)
		iounmap(hw->flash_address);
	pci_release_mem_regions(pdev);

	kfree(adapter->mac_table);
	kfree(adapter->shadow_vfta);
	free_netdev(netdev);

	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
}