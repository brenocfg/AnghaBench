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
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_2__ {int /*<<< orphan*/  sli_intf; } ;
struct lpfc_hba {scalar_t__ sli_rev; TYPE_1__ sli4_hba; } ;
struct bsg_job {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_2 ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* fc_bsg_to_shost (struct bsg_job*) ; 
 int lpfc_sli3_bsg_diag_loopback_mode (struct lpfc_hba*,struct bsg_job*) ; 
 int lpfc_sli4_bsg_diag_loopback_mode (struct lpfc_hba*,struct bsg_job*) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 struct lpfc_vport* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
lpfc_bsg_diag_loopback_mode(struct bsg_job *job)
{
	struct Scsi_Host *shost;
	struct lpfc_vport *vport;
	struct lpfc_hba *phba;
	int rc;

	shost = fc_bsg_to_shost(job);
	if (!shost)
		return -ENODEV;
	vport = shost_priv(shost);
	if (!vport)
		return -ENODEV;
	phba = vport->phba;
	if (!phba)
		return -ENODEV;

	if (phba->sli_rev < LPFC_SLI_REV4)
		rc = lpfc_sli3_bsg_diag_loopback_mode(phba, job);
	else if (bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf) >=
		 LPFC_SLI_INTF_IF_TYPE_2)
		rc = lpfc_sli4_bsg_diag_loopback_mode(phba, job);
	else
		rc = -ENODEV;

	return rc;
}