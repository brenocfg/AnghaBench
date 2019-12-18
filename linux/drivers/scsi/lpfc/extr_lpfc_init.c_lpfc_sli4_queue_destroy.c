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
struct TYPE_4__ {int sli_flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  lpfc_wq_list; int /*<<< orphan*/  mbx_cq; int /*<<< orphan*/  nvmels_cq; int /*<<< orphan*/  els_cq; int /*<<< orphan*/  dat_rq; int /*<<< orphan*/  hdr_rq; int /*<<< orphan*/  nvmels_wq; int /*<<< orphan*/  els_wq; int /*<<< orphan*/  mbx_wq; int /*<<< orphan*/  nvmet_mrq_data; int /*<<< orphan*/  nvmet_mrq_hdr; int /*<<< orphan*/  nvmet_cqset; scalar_t__ hdwq; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; TYPE_2__ sli; TYPE_1__ sli4_hba; int /*<<< orphan*/  cfg_nvmet_mrq; scalar_t__ nvmet_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int LPFC_QUEUE_FREE_INIT ; 
 int LPFC_QUEUE_FREE_WAIT ; 
 int /*<<< orphan*/  __lpfc_sli4_release_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_sli4_release_hdwq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_release_queues (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_sli4_queue_destroy(struct lpfc_hba *phba)
{
	/*
	 * Set FREE_INIT before beginning to free the queues.
	 * Wait until the users of queues to acknowledge to
	 * release queues by clearing FREE_WAIT.
	 */
	spin_lock_irq(&phba->hbalock);
	phba->sli.sli_flag |= LPFC_QUEUE_FREE_INIT;
	while (phba->sli.sli_flag & LPFC_QUEUE_FREE_WAIT) {
		spin_unlock_irq(&phba->hbalock);
		msleep(20);
		spin_lock_irq(&phba->hbalock);
	}
	spin_unlock_irq(&phba->hbalock);

	/* Release HBA eqs */
	if (phba->sli4_hba.hdwq)
		lpfc_sli4_release_hdwq(phba);

	if (phba->nvmet_support) {
		lpfc_sli4_release_queues(&phba->sli4_hba.nvmet_cqset,
					 phba->cfg_nvmet_mrq);

		lpfc_sli4_release_queues(&phba->sli4_hba.nvmet_mrq_hdr,
					 phba->cfg_nvmet_mrq);
		lpfc_sli4_release_queues(&phba->sli4_hba.nvmet_mrq_data,
					 phba->cfg_nvmet_mrq);
	}

	/* Release mailbox command work queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.mbx_wq);

	/* Release ELS work queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.els_wq);

	/* Release ELS work queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.nvmels_wq);

	/* Release unsolicited receive queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.hdr_rq);
	__lpfc_sli4_release_queue(&phba->sli4_hba.dat_rq);

	/* Release ELS complete queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.els_cq);

	/* Release NVME LS complete queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.nvmels_cq);

	/* Release mailbox command complete queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.mbx_cq);

	/* Everything on this list has been freed */
	INIT_LIST_HEAD(&phba->sli4_hba.lpfc_wq_list);

	/* Done with freeing the queues */
	spin_lock_irq(&phba->hbalock);
	phba->sli.sli_flag &= ~LPFC_QUEUE_FREE_INIT;
	spin_unlock_irq(&phba->hbalock);
}