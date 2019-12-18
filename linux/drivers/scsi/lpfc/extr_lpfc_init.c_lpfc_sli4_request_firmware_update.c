#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  sli_intf; } ;
struct lpfc_hba {char* ModelName; TYPE_1__* pcidev; TYPE_2__ sli4_hba; } ;
struct firmware {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELX_MODEL_NAME_SIZE ; 
 int EPERM ; 
 int /*<<< orphan*/  FW_ACTION_HOTPLUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ INT_FW_UPGRADE ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_2 ; 
 scalar_t__ RUN_FW_UPGRADE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  lpfc_write_firmware (struct firmware const*,void*) ; 
 int request_firmware (struct firmware const**,scalar_t__*,int /*<<< orphan*/ *) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/  (*) (struct firmware const*,void*)) ; 
 int /*<<< orphan*/  snprintf (scalar_t__*,int,char*,char*) ; 

int
lpfc_sli4_request_firmware_update(struct lpfc_hba *phba, uint8_t fw_upgrade)
{
	uint8_t file_name[ELX_MODEL_NAME_SIZE];
	int ret;
	const struct firmware *fw;

	/* Only supported on SLI4 interface type 2 for now */
	if (bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf) <
	    LPFC_SLI_INTF_IF_TYPE_2)
		return -EPERM;

	snprintf(file_name, ELX_MODEL_NAME_SIZE, "%s.grp", phba->ModelName);

	if (fw_upgrade == INT_FW_UPGRADE) {
		ret = request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
					file_name, &phba->pcidev->dev,
					GFP_KERNEL, (void *)phba,
					lpfc_write_firmware);
	} else if (fw_upgrade == RUN_FW_UPGRADE) {
		ret = request_firmware(&fw, file_name, &phba->pcidev->dev);
		if (!ret)
			lpfc_write_firmware(fw, (void *)phba);
	} else {
		ret = -EINVAL;
	}

	return ret;
}