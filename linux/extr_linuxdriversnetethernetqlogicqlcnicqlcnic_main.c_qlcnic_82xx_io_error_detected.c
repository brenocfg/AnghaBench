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
struct qlcnic_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  fw_work; struct net_device* netdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  __QLCNIC_AER ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_channel_io_normal ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  qlcnic_detach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_teardown_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pci_ers_result_t qlcnic_82xx_io_error_detected(struct pci_dev *pdev,
						      pci_channel_state_t state)
{
	struct qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	struct net_device *netdev = adapter->netdev;

	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	if (state == pci_channel_io_normal)
		return PCI_ERS_RESULT_RECOVERED;

	set_bit(__QLCNIC_AER, &adapter->state);
	netif_device_detach(netdev);

	cancel_delayed_work_sync(&adapter->fw_work);

	if (netif_running(netdev))
		qlcnic_down(adapter, netdev);

	qlcnic_detach(adapter);
	qlcnic_teardown_intr(adapter);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);

	pci_save_state(pdev);
	pci_disable_device(pdev);

	return PCI_ERS_RESULT_NEED_RESET;
}