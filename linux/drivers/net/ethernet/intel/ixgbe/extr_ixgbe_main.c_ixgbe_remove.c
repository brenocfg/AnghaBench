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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {scalar_t__ reg_state; } ;
struct ixgbe_adapter {int flags; int /*<<< orphan*/  state; int /*<<< orphan*/  af_xdp_zc_qps; TYPE_1__* rss_key; TYPE_1__* mac_table; TYPE_1__** jump_tables; int /*<<< orphan*/  io_addr; TYPE_1__* ixgbe_ieee_ets; TYPE_1__* ixgbe_ieee_pfc; int /*<<< orphan*/  hw; scalar_t__ mii_bus; int /*<<< orphan*/  service_task; struct net_device* netdev; } ;
struct TYPE_2__ {struct TYPE_2__* mask; struct TYPE_2__* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_DCA_CTRL ; 
 int /*<<< orphan*/  IXGBE_DCA_CTRL_DCA_DISABLE ; 
 int IXGBE_FLAG_DCA_ENABLED ; 
 int IXGBE_MAX_LINK_HANDLE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  __IXGBE_DISABLED ; 
 int /*<<< orphan*/  __IXGBE_REMOVING ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dca_remove_requester (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_dev_info (char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_clear_interrupt_scheme (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_dbg_adapter_exit (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_del_sanmac_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ixgbe_disable_sriov (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_release_hw_control (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_stop_ipsec_offload (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_sysfs_exit (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct ixgbe_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void ixgbe_remove(struct pci_dev *pdev)
{
	struct ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	struct net_device *netdev;
	bool disable_dev;
	int i;

	/* if !adapter then we already cleaned up in probe */
	if (!adapter)
		return;

	netdev  = adapter->netdev;
	ixgbe_dbg_adapter_exit(adapter);

	set_bit(__IXGBE_REMOVING, &adapter->state);
	cancel_work_sync(&adapter->service_task);

	if (adapter->mii_bus)
		mdiobus_unregister(adapter->mii_bus);

#ifdef CONFIG_IXGBE_DCA
	if (adapter->flags & IXGBE_FLAG_DCA_ENABLED) {
		adapter->flags &= ~IXGBE_FLAG_DCA_ENABLED;
		dca_remove_requester(&pdev->dev);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_DCA_CTRL,
				IXGBE_DCA_CTRL_DCA_DISABLE);
	}

#endif
#ifdef CONFIG_IXGBE_HWMON
	ixgbe_sysfs_exit(adapter);
#endif /* CONFIG_IXGBE_HWMON */

	/* remove the added san mac */
	ixgbe_del_sanmac_netdev(netdev);

#ifdef CONFIG_PCI_IOV
	ixgbe_disable_sriov(adapter);
#endif
	if (netdev->reg_state == NETREG_REGISTERED)
		unregister_netdev(netdev);

	ixgbe_stop_ipsec_offload(adapter);
	ixgbe_clear_interrupt_scheme(adapter);

	ixgbe_release_hw_control(adapter);

#ifdef CONFIG_DCB
	kfree(adapter->ixgbe_ieee_pfc);
	kfree(adapter->ixgbe_ieee_ets);

#endif
	iounmap(adapter->io_addr);
	pci_release_mem_regions(pdev);

	e_dev_info("complete\n");

	for (i = 0; i < IXGBE_MAX_LINK_HANDLE; i++) {
		if (adapter->jump_tables[i]) {
			kfree(adapter->jump_tables[i]->input);
			kfree(adapter->jump_tables[i]->mask);
		}
		kfree(adapter->jump_tables[i]);
	}

	kfree(adapter->mac_table);
	kfree(adapter->rss_key);
	bitmap_free(adapter->af_xdp_zc_qps);
	disable_dev = !test_and_set_bit(__IXGBE_DISABLED, &adapter->state);
	free_netdev(netdev);

	pci_disable_pcie_error_reporting(pdev);

	if (disable_dev)
		pci_disable_device(pdev);
}