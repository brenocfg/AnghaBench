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
typedef  size_t u32 ;
struct pm8001_hba_info {int /*<<< orphan*/  nvmd_completion; struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_ccb_info {int ccb_tag; int /*<<< orphan*/ * task; int /*<<< orphan*/  fw_control_context; } ;
struct fw_flash_Update_resp {int /*<<< orphan*/  status; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
#define  FLASH_UPDATE_COMPLETE_PENDING_REBOOT 136 
#define  FLASH_UPDATE_CRC_ERR 135 
#define  FLASH_UPDATE_DISABLED 134 
#define  FLASH_UPDATE_DNLD_NOT_SUPPORTED 133 
#define  FLASH_UPDATE_HDR_ERR 132 
#define  FLASH_UPDATE_HW_ERR 131 
#define  FLASH_UPDATE_IN_PROGRESS 130 
#define  FLASH_UPDATE_LENGTH_ERR 129 
#define  FLASH_UPDATE_OFFSET_ERR 128 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  pm8001_tag_free (struct pm8001_hba_info*,size_t) ; 

int pm8001_mpi_fw_flash_update_resp(struct pm8001_hba_info *pm8001_ha,
		void *piomb)
{
	u32 status;
	struct fw_flash_Update_resp *ppayload =
		(struct fw_flash_Update_resp *)(piomb + 4);
	u32 tag = le32_to_cpu(ppayload->tag);
	struct pm8001_ccb_info *ccb = &pm8001_ha->ccb_info[tag];
	status = le32_to_cpu(ppayload->status);
	switch (status) {
	case FLASH_UPDATE_COMPLETE_PENDING_REBOOT:
		PM8001_MSG_DBG(pm8001_ha,
		pm8001_printk(": FLASH_UPDATE_COMPLETE_PENDING_REBOOT\n"));
		break;
	case FLASH_UPDATE_IN_PROGRESS:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(": FLASH_UPDATE_IN_PROGRESS\n"));
		break;
	case FLASH_UPDATE_HDR_ERR:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(": FLASH_UPDATE_HDR_ERR\n"));
		break;
	case FLASH_UPDATE_OFFSET_ERR:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(": FLASH_UPDATE_OFFSET_ERR\n"));
		break;
	case FLASH_UPDATE_CRC_ERR:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(": FLASH_UPDATE_CRC_ERR\n"));
		break;
	case FLASH_UPDATE_LENGTH_ERR:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(": FLASH_UPDATE_LENGTH_ERR\n"));
		break;
	case FLASH_UPDATE_HW_ERR:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(": FLASH_UPDATE_HW_ERR\n"));
		break;
	case FLASH_UPDATE_DNLD_NOT_SUPPORTED:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(": FLASH_UPDATE_DNLD_NOT_SUPPORTED\n"));
		break;
	case FLASH_UPDATE_DISABLED:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(": FLASH_UPDATE_DISABLED\n"));
		break;
	default:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("No matched status = %d\n", status));
		break;
	}
	kfree(ccb->fw_control_context);
	ccb->task = NULL;
	ccb->ccb_tag = 0xFFFFFFFF;
	pm8001_tag_free(pm8001_ha, tag);
	complete(pm8001_ha->nvmd_completion);
	return 0;
}