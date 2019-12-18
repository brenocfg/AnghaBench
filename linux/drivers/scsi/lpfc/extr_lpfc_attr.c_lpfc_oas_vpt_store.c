#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_2__ {int /*<<< orphan*/  oas_next_lun; int /*<<< orphan*/  oas_next_vpt_wwpn; } ;
struct lpfc_hba {scalar_t__ cfg_oas_priority; scalar_t__ cfg_XLanePriority; TYPE_1__ sli4_hba; int /*<<< orphan*/  cfg_oas_flags; int /*<<< orphan*/  cfg_oas_vpt_wwpn; int /*<<< orphan*/  cfg_fof; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  FIND_FIRST_OAS_LUN ; 
 int /*<<< orphan*/  OAS_FIND_ANY_VPORT ; 
 int /*<<< orphan*/  OAS_LUN_VALID ; 
 int WWN_SZ ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int lpfc_wwn_set (char const*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ wwn_to_u64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
lpfc_oas_vpt_store(struct device *dev, struct device_attribute *attr,
		   const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct lpfc_hba *phba = ((struct lpfc_vport *)shost->hostdata)->phba;
	unsigned int cnt = count;
	uint8_t wwpn[WWN_SZ];
	int rc;

	if (!phba->cfg_fof)
		return -EPERM;

	/* count may include a LF at end of string */
	if (buf[cnt-1] == '\n')
		cnt--;

	rc = lpfc_wwn_set(buf, cnt, wwpn);
	if (rc)
		return rc;

	memcpy(phba->cfg_oas_vpt_wwpn, wwpn, (8 * sizeof(uint8_t)));
	memcpy(phba->sli4_hba.oas_next_vpt_wwpn, wwpn, (8 * sizeof(uint8_t)));
	if (wwn_to_u64(wwpn) == 0)
		phba->cfg_oas_flags |= OAS_FIND_ANY_VPORT;
	else
		phba->cfg_oas_flags &= ~OAS_FIND_ANY_VPORT;
	phba->cfg_oas_flags &= ~OAS_LUN_VALID;
	if (phba->cfg_oas_priority == 0)
		phba->cfg_oas_priority = phba->cfg_XLanePriority;
	phba->sli4_hba.oas_next_lun = FIND_FIRST_OAS_LUN;
	return count;
}