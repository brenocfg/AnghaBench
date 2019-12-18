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
struct pci_dev {int /*<<< orphan*/  revision; } ;
struct netxen_adapter {scalar_t__ portnum; int /*<<< orphan*/  state; int /*<<< orphan*/  tx_timeout_task; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __NX_RESETTING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  netxen_cancel_fw_work (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_cleanup_minidump (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_cleanup_pci_map (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_free_dummy_dma (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_free_ip_list (struct netxen_adapter*,int) ; 
 int /*<<< orphan*/  netxen_nic_detach (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_release_firmware (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_remove_diag_entries (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_set_interrupt_mode (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netxen_teardown_intr (struct netxen_adapter*) ; 
 int /*<<< orphan*/  nx_decr_dev_ref_cnt (struct netxen_adapter*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct netxen_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void netxen_nic_remove(struct pci_dev *pdev)
{
	struct netxen_adapter *adapter;
	struct net_device *netdev;

	adapter = pci_get_drvdata(pdev);
	if (adapter == NULL)
		return;

	netdev = adapter->netdev;

	netxen_cancel_fw_work(adapter);

	unregister_netdev(netdev);

	cancel_work_sync(&adapter->tx_timeout_task);

	netxen_free_ip_list(adapter, false);
	netxen_nic_detach(adapter);

	nx_decr_dev_ref_cnt(adapter);

	if (adapter->portnum == 0)
		netxen_free_dummy_dma(adapter);

	clear_bit(__NX_RESETTING, &adapter->state);

	netxen_teardown_intr(adapter);
	netxen_set_interrupt_mode(adapter, 0);
	netxen_remove_diag_entries(adapter);

	netxen_cleanup_pci_map(adapter);

	netxen_release_firmware(adapter);

	if (NX_IS_REVISION_P3(pdev->revision)) {
		netxen_cleanup_minidump(adapter);
		pci_disable_pcie_error_reporting(pdev);
	}

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	free_netdev(netdev);
}