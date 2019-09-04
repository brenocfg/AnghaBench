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
struct qlcnic_hardware_context {struct qlcnic_hardware_context* fw_info; int /*<<< orphan*/  mailbox; } ;
struct qlcnic_adapter {int /*<<< orphan*/ * qlcnic_wq; struct qlcnic_hardware_context* ahw; int /*<<< orphan*/  state; struct qlcnic_hardware_context* eswitch; struct qlcnic_hardware_context* npars; int /*<<< orphan*/  dcb; int /*<<< orphan*/  idc_aen_work; struct net_device* netdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct qlcnic_hardware_context*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_detach_mailbox_work (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_free_mailbox (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_free_mbx_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_initialize_nic (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_cancel_idc_work (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_cleanup_pci_map (struct qlcnic_hardware_context*) ; 
 int /*<<< orphan*/  qlcnic_clr_all_drv_state (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_dcb_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_detach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_free_adapter_resources (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_free_lb_filters_mem (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_release_firmware (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_remove_sysfs (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_cleanup (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_disable (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_teardown_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_unregister_hwmon_dev (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void qlcnic_remove(struct pci_dev *pdev)
{
	struct qlcnic_adapter *adapter;
	struct net_device *netdev;
	struct qlcnic_hardware_context *ahw;

	adapter = pci_get_drvdata(pdev);
	if (adapter == NULL)
		return;

	netdev = adapter->netdev;

	qlcnic_cancel_idc_work(adapter);
	qlcnic_sriov_pf_disable(adapter);
	ahw = adapter->ahw;

	unregister_netdev(netdev);
	qlcnic_sriov_cleanup(adapter);

	if (qlcnic_83xx_check(adapter)) {
		qlcnic_83xx_initialize_nic(adapter, 0);
		cancel_delayed_work_sync(&adapter->idc_aen_work);
		qlcnic_83xx_free_mbx_intr(adapter);
		qlcnic_83xx_detach_mailbox_work(adapter);
		qlcnic_83xx_free_mailbox(ahw->mailbox);
		kfree(ahw->fw_info);
	}

	qlcnic_dcb_free(adapter->dcb);
	qlcnic_detach(adapter);
	kfree(adapter->npars);
	kfree(adapter->eswitch);

	if (qlcnic_82xx_check(adapter))
		qlcnic_clr_all_drv_state(adapter, 0);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);

	qlcnic_free_lb_filters_mem(adapter);

	qlcnic_teardown_intr(adapter);

	qlcnic_remove_sysfs(adapter);

	qlcnic_unregister_hwmon_dev(adapter);

	qlcnic_cleanup_pci_map(adapter->ahw);

	qlcnic_release_firmware(adapter);

	pci_disable_pcie_error_reporting(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	if (adapter->qlcnic_wq) {
		destroy_workqueue(adapter->qlcnic_wq);
		adapter->qlcnic_wq = NULL;
	}

	qlcnic_free_adapter_resources(adapter);
	kfree(ahw);
	free_netdev(netdev);
}