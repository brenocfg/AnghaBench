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
typedef  scalar_t__ uint8_t ;
struct lpfc_hba {int /*<<< orphan*/  sli_rev; scalar_t__ pci_dev_grp; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ LPFC_PCI_DEV_OC ; 
 int /*<<< orphan*/  LPFC_SLI_REV4 ; 
 int lpfc_init_api_table_setup (struct lpfc_hba*,scalar_t__) ; 
 int lpfc_mbox_api_table_setup (struct lpfc_hba*,scalar_t__) ; 
 int lpfc_scsi_api_table_setup (struct lpfc_hba*,scalar_t__) ; 
 int lpfc_sli_api_table_setup (struct lpfc_hba*,scalar_t__) ; 

int
lpfc_api_table_setup(struct lpfc_hba *phba, uint8_t dev_grp)
{
	int rc;

	/* Set up lpfc PCI-device group */
	phba->pci_dev_grp = dev_grp;

	/* The LPFC_PCI_DEV_OC uses SLI4 */
	if (dev_grp == LPFC_PCI_DEV_OC)
		phba->sli_rev = LPFC_SLI_REV4;

	/* Set up device INIT API function jump table */
	rc = lpfc_init_api_table_setup(phba, dev_grp);
	if (rc)
		return -ENODEV;
	/* Set up SCSI API function jump table */
	rc = lpfc_scsi_api_table_setup(phba, dev_grp);
	if (rc)
		return -ENODEV;
	/* Set up SLI API function jump table */
	rc = lpfc_sli_api_table_setup(phba, dev_grp);
	if (rc)
		return -ENODEV;
	/* Set up MBOX API function jump table */
	rc = lpfc_mbox_api_table_setup(phba, dev_grp);
	if (rc)
		return -ENODEV;

	return 0;
}