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
struct lpfc_vport {int dummy; } ;
struct lpfc_hba {int max_vports; int defer_flogi_acc_flag; int /*<<< orphan*/  hba_flag; TYPE_1__* pport; int /*<<< orphan*/  fabric_block_timer; int /*<<< orphan*/  bit_flags; int /*<<< orphan*/  link_state; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_2__ {scalar_t__ rcv_flogi_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FABRIC_COMANDS_BLOCKED ; 
 int /*<<< orphan*/  HBA_FLOGI_ISSUED ; 
 int /*<<< orphan*/  LPFC_LINK_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_linkup_port (struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_linkup(struct lpfc_hba *phba)
{
	struct lpfc_vport **vports;
	int i;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(phba->pport);

	phba->link_state = LPFC_LINK_UP;

	/* Unblock fabric iocbs if they are blocked */
	clear_bit(FABRIC_COMANDS_BLOCKED, &phba->bit_flags);
	del_timer_sync(&phba->fabric_block_timer);

	vports = lpfc_create_vport_work_array(phba);
	if (vports != NULL)
		for (i = 0; i <= phba->max_vports && vports[i] != NULL; i++)
			lpfc_linkup_port(vports[i]);
	lpfc_destroy_vport_work_array(phba, vports);

	/* Clear the pport flogi counter in case the link down was
	 * absorbed without an ACQE. No lock here - in worker thread
	 * and discovery is synchronized.
	 */
	spin_lock_irq(shost->host_lock);
	phba->pport->rcv_flogi_cnt = 0;
	spin_unlock_irq(shost->host_lock);

	/* reinitialize initial FLOGI flag */
	phba->hba_flag &= ~(HBA_FLOGI_ISSUED);
	phba->defer_flogi_acc_flag = false;

	return 0;
}