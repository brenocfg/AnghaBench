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
typedef  int uint8_t ;
struct lpfc_hba {int /*<<< orphan*/  lpfc_get_iocb_from_iocbq; int /*<<< orphan*/  __lpfc_sli_release_iocbq; int /*<<< orphan*/  __lpfc_sli_issue_iocb; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_PCI_DEV_LP 129 
#define  LPFC_PCI_DEV_OC 128 
 int /*<<< orphan*/  __lpfc_sli_issue_iocb_s3 ; 
 int /*<<< orphan*/  __lpfc_sli_issue_iocb_s4 ; 
 int /*<<< orphan*/  __lpfc_sli_release_iocbq_s3 ; 
 int /*<<< orphan*/  __lpfc_sli_release_iocbq_s4 ; 
 int /*<<< orphan*/  lpfc_get_iocb_from_iocbq ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
lpfc_sli_api_table_setup(struct lpfc_hba *phba, uint8_t dev_grp)
{

	switch (dev_grp) {
	case LPFC_PCI_DEV_LP:
		phba->__lpfc_sli_issue_iocb = __lpfc_sli_issue_iocb_s3;
		phba->__lpfc_sli_release_iocbq = __lpfc_sli_release_iocbq_s3;
		break;
	case LPFC_PCI_DEV_OC:
		phba->__lpfc_sli_issue_iocb = __lpfc_sli_issue_iocb_s4;
		phba->__lpfc_sli_release_iocbq = __lpfc_sli_release_iocbq_s4;
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1419 Invalid HBA PCI-device group: 0x%x\n",
				dev_grp);
		return -ENODEV;
		break;
	}
	phba->lpfc_get_iocb_from_iocbq = lpfc_get_iocb_from_iocbq;
	return 0;
}