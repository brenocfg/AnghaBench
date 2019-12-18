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
struct pci_dev {int dummy; } ;
struct beiscsi_hba {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int beiscsi_check_fw_rdy (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pci_ers_result_t beiscsi_eeh_reset(struct pci_dev *pdev)
{
	struct beiscsi_hba *phba = NULL;
	int status = 0;

	phba = (struct beiscsi_hba *)pci_get_drvdata(pdev);

	beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
		    "BM_%d : EEH Reset\n");

	status = pci_enable_device(pdev);
	if (status)
		return PCI_ERS_RESULT_DISCONNECT;

	pci_set_master(pdev);
	pci_set_power_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	status = beiscsi_check_fw_rdy(phba);
	if (status) {
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : EEH Reset Completed\n");
	} else {
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : EEH Reset Completion Failure\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	return PCI_ERS_RESULT_RECOVERED;
}