#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lpfc_sli {int /*<<< orphan*/  sli_flag; TYPE_4__* mbox_active; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  link_state; TYPE_2__* pport; struct lpfc_sli sli; } ;
struct TYPE_7__ {int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_5__ {TYPE_3__ mb; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  work_port_lock; int /*<<< orphan*/  work_port_events; int /*<<< orphan*/  port_state; } ;
typedef  TYPE_3__ MAILBOX_t ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int LOG_MBOX ; 
 int LOG_SLI ; 
 int /*<<< orphan*/  LPFC_LINK_UNKNOWN ; 
 int /*<<< orphan*/  LPFC_SLI_ACTIVE ; 
 int /*<<< orphan*/  WORKER_MBOX_TMO ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  lpfc_reset_hba (struct lpfc_hba*) ; 
 scalar_t__ lpfc_sli4_process_missed_mbox_completions (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_abort_fcp_rings (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_mbox_timeout_handler(struct lpfc_hba *phba)
{
	LPFC_MBOXQ_t *pmbox = phba->sli.mbox_active;
	MAILBOX_t *mb = NULL;

	struct lpfc_sli *psli = &phba->sli;

	/* If the mailbox completed, process the completion and return */
	if (lpfc_sli4_process_missed_mbox_completions(phba))
		return;

	if (pmbox != NULL)
		mb = &pmbox->u.mb;
	/* Check the pmbox pointer first.  There is a race condition
	 * between the mbox timeout handler getting executed in the
	 * worklist and the mailbox actually completing. When this
	 * race condition occurs, the mbox_active will be NULL.
	 */
	spin_lock_irq(&phba->hbalock);
	if (pmbox == NULL) {
		lpfc_printf_log(phba, KERN_WARNING,
				LOG_MBOX | LOG_SLI,
				"0353 Active Mailbox cleared - mailbox timeout "
				"exiting\n");
		spin_unlock_irq(&phba->hbalock);
		return;
	}

	/* Mbox cmd <mbxCommand> timeout */
	lpfc_printf_log(phba, KERN_ERR, LOG_MBOX | LOG_SLI,
			"0310 Mailbox command x%x timeout Data: x%x x%x x%px\n",
			mb->mbxCommand,
			phba->pport->port_state,
			phba->sli.sli_flag,
			phba->sli.mbox_active);
	spin_unlock_irq(&phba->hbalock);

	/* Setting state unknown so lpfc_sli_abort_iocb_ring
	 * would get IOCB_ERROR from lpfc_sli_issue_iocb, allowing
	 * it to fail all outstanding SCSI IO.
	 */
	spin_lock_irq(&phba->pport->work_port_lock);
	phba->pport->work_port_events &= ~WORKER_MBOX_TMO;
	spin_unlock_irq(&phba->pport->work_port_lock);
	spin_lock_irq(&phba->hbalock);
	phba->link_state = LPFC_LINK_UNKNOWN;
	psli->sli_flag &= ~LPFC_SLI_ACTIVE;
	spin_unlock_irq(&phba->hbalock);

	lpfc_sli_abort_fcp_rings(phba);

	lpfc_printf_log(phba, KERN_ERR, LOG_MBOX | LOG_SLI,
			"0345 Resetting board due to mailbox timeout\n");

	/* Reset the HBA device */
	lpfc_reset_hba(phba);
}