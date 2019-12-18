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
struct be_adapter {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_CLEAR_ALL ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  be_clear_error (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int be_fw_wait_ready (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct be_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t be_eeh_reset(struct pci_dev *pdev)
{
	struct be_adapter *adapter = pci_get_drvdata(pdev);
	int status;

	dev_info(&adapter->pdev->dev, "EEH reset\n");

	status = pci_enable_device(pdev);
	if (status)
		return PCI_ERS_RESULT_DISCONNECT;

	pci_set_master(pdev);
	pci_restore_state(pdev);

	/* Check if card is ok and fw is ready */
	dev_info(&adapter->pdev->dev,
		 "Waiting for FW to be ready after EEH reset\n");
	status = be_fw_wait_ready(adapter);
	if (status)
		return PCI_ERS_RESULT_DISCONNECT;

	be_clear_error(adapter, BE_CLEAR_ALL);
	return PCI_ERS_RESULT_RECOVERED;
}