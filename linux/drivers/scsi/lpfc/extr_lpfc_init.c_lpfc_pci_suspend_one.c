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
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int pci_dev_grp; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_PCI_DEV_LP 129 
#define  LPFC_PCI_DEV_OC 128 
 int lpfc_pci_suspend_one_s3 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int lpfc_pci_suspend_one_s4 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static int
lpfc_pci_suspend_one(struct pci_dev *pdev, pm_message_t msg)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct lpfc_hba *phba = ((struct lpfc_vport *)shost->hostdata)->phba;
	int rc = -ENODEV;

	switch (phba->pci_dev_grp) {
	case LPFC_PCI_DEV_LP:
		rc = lpfc_pci_suspend_one_s3(pdev, msg);
		break;
	case LPFC_PCI_DEV_OC:
		rc = lpfc_pci_suspend_one_s4(pdev, msg);
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1425 Invalid PCI device group: 0x%x\n",
				phba->pci_dev_grp);
		break;
	}
	return rc;
}