#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  num_disc_nodes; int /*<<< orphan*/  fc_prli_sent; } ;
struct lpfc_nodelist {int /*<<< orphan*/  fc4_prli_sent; int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_flag; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ulpWord; } ;
struct TYPE_7__ {TYPE_2__ un; scalar_t__ ulpStatus; } ;
struct TYPE_5__ {struct lpfc_iocbq* rsp_iocb; } ;
struct lpfc_iocbq {scalar_t__ context1; TYPE_3__ iocb; TYPE_1__ context_un; struct lpfc_vport* vport; } ;
struct lpfc_hba {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_3__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 int /*<<< orphan*/  NLP_EVT_CMPL_PRLI ; 
 int /*<<< orphan*/  NLP_PRLI_SND ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_disc_state_machine (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_els_chk_latt (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 scalar_t__ lpfc_els_retry (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ; 
 scalar_t__ lpfc_error_lost_link (TYPE_3__*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_cmpl_els_prli(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
		   struct lpfc_iocbq *rspiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	IOCB_t *irsp;
	struct lpfc_nodelist *ndlp;

	/* we pass cmdiocb to state machine which needs rspiocb as well */
	cmdiocb->context_un.rsp_iocb = rspiocb;

	irsp = &(rspiocb->iocb);
	ndlp = (struct lpfc_nodelist *) cmdiocb->context1;
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag &= ~NLP_PRLI_SND;

	/* Driver supports multiple FC4 types.  Counters matter. */
	vport->fc_prli_sent--;
	ndlp->fc4_prli_sent--;
	spin_unlock_irq(shost->host_lock);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"PRLI cmpl:       status:x%x/x%x did:x%x",
		irsp->ulpStatus, irsp->un.ulpWord[4],
		ndlp->nlp_DID);

	/* PRLI completes to NPort <nlp_DID> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0103 PRLI completes to NPort x%06x "
			 "Data: x%x x%x x%x x%x\n",
			 ndlp->nlp_DID, irsp->ulpStatus, irsp->un.ulpWord[4],
			 vport->num_disc_nodes, ndlp->fc4_prli_sent);

	/* Check to see if link went down during discovery */
	if (lpfc_els_chk_latt(vport))
		goto out;

	if (irsp->ulpStatus) {
		/* Check for retry */
		if (lpfc_els_retry(phba, cmdiocb, rspiocb)) {
			/* ELS command is being retried */
			goto out;
		}

		/* PRLI failed */
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "2754 PRLI failure DID:%06X Status:x%x/x%x, "
				 "data: x%x\n",
				 ndlp->nlp_DID, irsp->ulpStatus,
				 irsp->un.ulpWord[4], ndlp->fc4_prli_sent);

		/* Do not call DSM for lpfc_els_abort'ed ELS cmds */
		if (lpfc_error_lost_link(irsp))
			goto out;
		else
			lpfc_disc_state_machine(vport, ndlp, cmdiocb,
						NLP_EVT_CMPL_PRLI);
	} else {
		/* Good status, call state machine.  However, if another
		 * PRLI is outstanding, don't call the state machine
		 * because final disposition to Mapped or Unmapped is
		 * completed there.
		 */
		lpfc_disc_state_machine(vport, ndlp, cmdiocb,
					NLP_EVT_CMPL_PRLI);
	}

out:
	lpfc_els_free_iocb(phba, cmdiocb);
	return;
}