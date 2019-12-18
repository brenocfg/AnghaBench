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
struct pci_dev {scalar_t__ devfn; } ;
struct be_adapter {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_ERROR_EEH ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  be_cancel_err_detection (struct be_adapter*) ; 
 int /*<<< orphan*/  be_check_error (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cleanup (struct be_adapter*) ; 
 int /*<<< orphan*/  be_roce_dev_remove (struct be_adapter*) ; 
 int /*<<< orphan*/  be_set_error (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct be_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static pci_ers_result_t be_eeh_err_detected(struct pci_dev *pdev,
					    pci_channel_state_t state)
{
	struct be_adapter *adapter = pci_get_drvdata(pdev);

	dev_err(&adapter->pdev->dev, "EEH error detected\n");

	be_roce_dev_remove(adapter);

	if (!be_check_error(adapter, BE_ERROR_EEH)) {
		be_set_error(adapter, BE_ERROR_EEH);

		be_cancel_err_detection(adapter);

		be_cleanup(adapter);
	}

	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	pci_disable_device(pdev);

	/* The error could cause the FW to trigger a flash debug dump.
	 * Resetting the card while flash dump is in progress
	 * can cause it not to recover; wait for it to finish.
	 * Wait only for first function as it is needed only once per
	 * adapter.
	 */
	if (pdev->devfn == 0)
		ssleep(30);

	return PCI_ERS_RESULT_NEED_RESET;
}