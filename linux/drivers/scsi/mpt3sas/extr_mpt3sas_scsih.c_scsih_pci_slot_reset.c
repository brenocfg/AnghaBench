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
struct Scsi_Host {int dummy; } ;
struct MPT3SAS_ADAPTER {struct pci_dev* pdev; scalar_t__ pci_error_recovery; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_BIG_HAMMER ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*) ; 
 int /*<<< orphan*/  ioc_warn (struct MPT3SAS_ADAPTER*,char*,char*) ; 
 int mpt3sas_base_hard_reset_handler (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int mpt3sas_base_map_resources (struct MPT3SAS_ADAPTER*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static pci_ers_result_t
scsih_pci_slot_reset(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	int rc;

	ioc_info(ioc, "PCI error: slot reset callback!!\n");

	ioc->pci_error_recovery = 0;
	ioc->pdev = pdev;
	pci_restore_state(pdev);
	rc = mpt3sas_base_map_resources(ioc);
	if (rc)
		return PCI_ERS_RESULT_DISCONNECT;

	rc = mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);

	ioc_warn(ioc, "hard reset: %s\n",
		 (rc == 0) ? "success" : "failed");

	if (!rc)
		return PCI_ERS_RESULT_RECOVERED;
	else
		return PCI_ERS_RESULT_DISCONNECT;
}