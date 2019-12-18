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
struct lpfc_vport {int fc_rscn_flush; int fc_rscn_id_cnt; int fc_flag; int /*<<< orphan*/ ** fc_rscn_id_list; struct lpfc_hba* phba; } ;
struct lpfc_hba {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int FC_RSCN_DISCOVERY ; 
 int FC_RSCN_MODE ; 
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_in_buf_free (struct lpfc_hba*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_els_flush_rscn(struct lpfc_vport *vport)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;
	int i;

	spin_lock_irq(shost->host_lock);
	if (vport->fc_rscn_flush) {
		/* Another thread is walking fc_rscn_id_list on this vport */
		spin_unlock_irq(shost->host_lock);
		return;
	}
	/* Indicate we are walking lpfc_els_flush_rscn on this vport */
	vport->fc_rscn_flush = 1;
	spin_unlock_irq(shost->host_lock);

	for (i = 0; i < vport->fc_rscn_id_cnt; i++) {
		lpfc_in_buf_free(phba, vport->fc_rscn_id_list[i]);
		vport->fc_rscn_id_list[i] = NULL;
	}
	spin_lock_irq(shost->host_lock);
	vport->fc_rscn_id_cnt = 0;
	vport->fc_flag &= ~(FC_RSCN_MODE | FC_RSCN_DISCOVERY);
	spin_unlock_irq(shost->host_lock);
	lpfc_can_disctmo(vport);
	/* Indicate we are done walking this fc_rscn_id_list */
	vport->fc_rscn_flush = 0;
}