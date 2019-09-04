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
struct pci_dev {int /*<<< orphan*/  error_state; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  __QLCNIC_AER ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_channel_io_normal ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_aer_reset (struct qlcnic_adapter*) ; 

__attribute__((used)) static pci_ers_result_t qlcnic_83xx_io_slot_reset(struct pci_dev *pdev)
{
	struct qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	int err = 0;

	pdev->error_state = pci_channel_io_normal;
	err = pci_enable_device(pdev);
	if (err)
		goto disconnect;

	pci_set_power_state(pdev, PCI_D0);
	pci_set_master(pdev);
	pci_restore_state(pdev);

	err = qlcnic_83xx_aer_reset(adapter);
	if (err == 0)
		return PCI_ERS_RESULT_RECOVERED;
disconnect:
	clear_bit(__QLCNIC_AER, &adapter->state);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	return PCI_ERS_RESULT_DISCONNECT;
}