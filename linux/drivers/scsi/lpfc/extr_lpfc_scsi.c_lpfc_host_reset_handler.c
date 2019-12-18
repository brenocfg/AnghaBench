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
struct scsi_cmnd {TYPE_1__* device; } ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_FCP ; 
 int /*<<< orphan*/  LPFC_MBX_WAIT ; 
 int SUCCESS ; 
 int /*<<< orphan*/  lpfc_offline (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline_prep (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int lpfc_online (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int lpfc_sli_brdrestart (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unblock_mgmt_io (struct lpfc_hba*) ; 

__attribute__((used)) static int
lpfc_host_reset_handler(struct scsi_cmnd *cmnd)
{
	struct Scsi_Host *shost = cmnd->device->host;
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba *phba = vport->phba;
	int rc, ret = SUCCESS;

	lpfc_printf_vlog(vport, KERN_ERR, LOG_FCP,
			 "3172 SCSI layer issued Host Reset Data:\n");

	lpfc_offline_prep(phba, LPFC_MBX_WAIT);
	lpfc_offline(phba);
	rc = lpfc_sli_brdrestart(phba);
	if (rc)
		goto error;

	rc = lpfc_online(phba);
	if (rc)
		goto error;

	lpfc_unblock_mgmt_io(phba);

	return ret;
error:
	lpfc_printf_vlog(vport, KERN_ERR, LOG_FCP,
			 "3323 Failed host reset\n");
	lpfc_unblock_mgmt_io(phba);
	return FAILED;
}