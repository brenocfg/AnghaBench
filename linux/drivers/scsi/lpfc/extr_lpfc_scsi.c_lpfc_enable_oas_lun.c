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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct lpfc_name {int dummy; } ;
struct lpfc_hba {int /*<<< orphan*/  devicelock; int /*<<< orphan*/  luns; int /*<<< orphan*/  cfg_fof; } ;
struct lpfc_device_data {int oas_enabled; int available; int /*<<< orphan*/  listentry; void* priority; } ;

/* Variables and functions */
 struct lpfc_device_data* __lpfc_get_device_data (struct lpfc_hba*,int /*<<< orphan*/ *,struct lpfc_name*,struct lpfc_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lpfc_device_data* lpfc_create_device_data (struct lpfc_hba*,struct lpfc_name*,struct lpfc_name*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

bool
lpfc_enable_oas_lun(struct lpfc_hba *phba, struct lpfc_name *vport_wwpn,
		    struct lpfc_name *target_wwpn, uint64_t lun, uint8_t pri)
{

	struct lpfc_device_data *lun_info;
	unsigned long flags;

	if (unlikely(!phba) || !vport_wwpn || !target_wwpn ||
	    !phba->cfg_fof)
		return false;

	spin_lock_irqsave(&phba->devicelock, flags);

	/* Check to see if the device data for the lun has been created */
	lun_info = __lpfc_get_device_data(phba, &phba->luns, vport_wwpn,
					  target_wwpn, lun);
	if (lun_info) {
		if (!lun_info->oas_enabled)
			lun_info->oas_enabled = true;
		lun_info->priority = pri;
		spin_unlock_irqrestore(&phba->devicelock, flags);
		return true;
	}

	/* Create an lun info structure and add to list of luns */
	lun_info = lpfc_create_device_data(phba, vport_wwpn, target_wwpn, lun,
					   pri, true);
	if (lun_info) {
		lun_info->oas_enabled = true;
		lun_info->priority = pri;
		lun_info->available = false;
		list_add_tail(&lun_info->listentry, &phba->luns);
		spin_unlock_irqrestore(&phba->devicelock, flags);
		return true;
	}
	spin_unlock_irqrestore(&phba->devicelock, flags);
	return false;
}