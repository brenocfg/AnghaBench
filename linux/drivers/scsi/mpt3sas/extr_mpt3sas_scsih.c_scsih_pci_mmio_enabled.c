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
struct MPT3SAS_ADAPTER {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static pci_ers_result_t
scsih_pci_mmio_enabled(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	ioc_info(ioc, "PCI error: mmio enabled callback!!\n");

	/* TODO - dump whatever for debugging purposes */

	/* This called only if scsih_pci_error_detected returns
	 * PCI_ERS_RESULT_CAN_RECOVER. Read/write to the device still
	 * works, no need to reset slot.
	 */
	return PCI_ERS_RESULT_RECOVERED;
}