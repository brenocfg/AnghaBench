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
struct lpfc_vport {int fc_flag; scalar_t__ fc_rscn_id_cnt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int FC_RSCN_DISCOVERY ; 
 int FC_RSCN_MODE ; 
 int /*<<< orphan*/  lpfc_els_handle_rscn (struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_end_rscn(struct lpfc_vport *vport)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	if (vport->fc_flag & FC_RSCN_MODE) {
		/*
		 * Check to see if more RSCNs came in while we were
		 * processing this one.
		 */
		if (vport->fc_rscn_id_cnt ||
		    (vport->fc_flag & FC_RSCN_DISCOVERY) != 0)
			lpfc_els_handle_rscn(vport);
		else {
			spin_lock_irq(shost->host_lock);
			vport->fc_flag &= ~FC_RSCN_MODE;
			spin_unlock_irq(shost->host_lock);
		}
	}
}