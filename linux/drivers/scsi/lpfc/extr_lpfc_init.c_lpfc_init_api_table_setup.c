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
struct lpfc_hba {int /*<<< orphan*/  lpfc_stop_port; int /*<<< orphan*/  lpfc_handle_eratt; int /*<<< orphan*/  lpfc_hba_down_post; int /*<<< orphan*/  lpfc_selective_reset; int /*<<< orphan*/  lpfc_hba_down_link; int /*<<< orphan*/  lpfc_hba_init_link; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_PCI_DEV_LP 129 
#define  LPFC_PCI_DEV_OC 128 
 int /*<<< orphan*/  lpfc_handle_eratt_s3 ; 
 int /*<<< orphan*/  lpfc_handle_eratt_s4 ; 
 int /*<<< orphan*/  lpfc_hba_down_link ; 
 int /*<<< orphan*/  lpfc_hba_down_post_s3 ; 
 int /*<<< orphan*/  lpfc_hba_down_post_s4 ; 
 int /*<<< orphan*/  lpfc_hba_init_link ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpfc_selective_reset ; 
 int /*<<< orphan*/  lpfc_stop_port_s3 ; 
 int /*<<< orphan*/  lpfc_stop_port_s4 ; 

int
lpfc_init_api_table_setup(struct lpfc_hba *phba, uint8_t dev_grp)
{
	phba->lpfc_hba_init_link = lpfc_hba_init_link;
	phba->lpfc_hba_down_link = lpfc_hba_down_link;
	phba->lpfc_selective_reset = lpfc_selective_reset;
	switch (dev_grp) {
	case LPFC_PCI_DEV_LP:
		phba->lpfc_hba_down_post = lpfc_hba_down_post_s3;
		phba->lpfc_handle_eratt = lpfc_handle_eratt_s3;
		phba->lpfc_stop_port = lpfc_stop_port_s3;
		break;
	case LPFC_PCI_DEV_OC:
		phba->lpfc_hba_down_post = lpfc_hba_down_post_s4;
		phba->lpfc_handle_eratt = lpfc_handle_eratt_s4;
		phba->lpfc_stop_port = lpfc_stop_port_s4;
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1431 Invalid HBA PCI-device group: 0x%x\n",
				dev_grp);
		return -ENODEV;
		break;
	}
	return 0;
}