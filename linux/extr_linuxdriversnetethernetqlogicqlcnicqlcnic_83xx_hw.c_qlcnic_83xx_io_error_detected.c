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
struct qlcnic_adapter {int /*<<< orphan*/  state; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  __QLCNIC_AER ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 scalar_t__ pci_channel_io_normal ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  qlcnic_83xx_aer_stop_poll_work (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pci_ers_result_t qlcnic_83xx_io_error_detected(struct pci_dev *pdev,
						      pci_channel_state_t state)
{
	struct qlcnic_adapter *adapter = pci_get_drvdata(pdev);

	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	if (state == pci_channel_io_normal)
		return PCI_ERS_RESULT_RECOVERED;

	set_bit(__QLCNIC_AER, &adapter->state);
	set_bit(__QLCNIC_RESETTING, &adapter->state);

	qlcnic_83xx_aer_stop_poll_work(adapter);

	pci_save_state(pdev);
	pci_disable_device(pdev);

	return PCI_ERS_RESULT_NEED_RESET;
}