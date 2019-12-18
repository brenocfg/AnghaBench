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
typedef  scalar_t__ uint64_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int cfg_oas_flags; int /*<<< orphan*/  cfg_oas_priority; int /*<<< orphan*/  cfg_oas_lun_status; int /*<<< orphan*/  cfg_oas_tgt_wwpn; int /*<<< orphan*/  cfg_oas_vpt_wwpn; int /*<<< orphan*/  cfg_fof; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EFAULT ; 
 int EPERM ; 
 scalar_t__ NOT_OAS_ENABLED_LUN ; 
 int OAS_FIND_ANY_TARGET ; 
 int OAS_FIND_ANY_VPORT ; 
 int OAS_LUN_VALID ; 
 scalar_t__ PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 scalar_t__ lpfc_oas_lun_get_next (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,scalar_t__) ; 
 scalar_t__ wwn_to_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
lpfc_oas_lun_show(struct device *dev, struct device_attribute *attr,
		  char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct lpfc_hba *phba = ((struct lpfc_vport *)shost->hostdata)->phba;

	uint64_t oas_lun;
	int len = 0;

	if (!phba->cfg_fof)
		return -EPERM;

	if (wwn_to_u64(phba->cfg_oas_vpt_wwpn) == 0)
		if (!(phba->cfg_oas_flags & OAS_FIND_ANY_VPORT))
			return -EFAULT;

	if (wwn_to_u64(phba->cfg_oas_tgt_wwpn) == 0)
		if (!(phba->cfg_oas_flags & OAS_FIND_ANY_TARGET))
			return -EFAULT;

	oas_lun = lpfc_oas_lun_get_next(phba, phba->cfg_oas_vpt_wwpn,
					phba->cfg_oas_tgt_wwpn,
					&phba->cfg_oas_lun_status,
					&phba->cfg_oas_priority);
	if (oas_lun != NOT_OAS_ENABLED_LUN)
		phba->cfg_oas_flags |= OAS_LUN_VALID;

	len += scnprintf(buf + len, PAGE_SIZE-len, "0x%llx", oas_lun);

	return len;
}