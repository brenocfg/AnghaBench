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
typedef  size_t uint32_t ;
struct lpfc_sli4_hba {int /*<<< orphan*/  (* sli4_write_eq_db ) (struct lpfc_hba*,struct lpfc_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sli4_eq_clr_intr ) (struct lpfc_queue*) ;TYPE_2__* mbx_cq; TYPE_1__* hba_eq_hdl; scalar_t__ hdwq; } ;
struct lpfc_queue {scalar_t__ queue_id; } ;
struct lpfc_hba {scalar_t__ sli_rev; size_t cfg_irq_chann; struct lpfc_sli4_hba sli4_hba; } ;
struct TYPE_4__ {scalar_t__ assoc_qid; } ;
struct TYPE_3__ {struct lpfc_queue* eq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_QUEUE_REARM ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int lpfc_sli4_mbox_completions_pending (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_process_eq (struct lpfc_hba*,struct lpfc_queue*) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_queue*) ; 
 int /*<<< orphan*/  stub2 (struct lpfc_hba*,struct lpfc_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
lpfc_sli4_process_missed_mbox_completions(struct lpfc_hba *phba)
{
	struct lpfc_sli4_hba *sli4_hba = &phba->sli4_hba;
	uint32_t eqidx;
	struct lpfc_queue *fpeq = NULL;
	struct lpfc_queue *eq;
	bool mbox_pending;

	if (unlikely(!phba) || (phba->sli_rev != LPFC_SLI_REV4))
		return false;

	/* Find the EQ associated with the mbox CQ */
	if (sli4_hba->hdwq) {
		for (eqidx = 0; eqidx < phba->cfg_irq_chann; eqidx++) {
			eq = phba->sli4_hba.hba_eq_hdl[eqidx].eq;
			if (eq && eq->queue_id == sli4_hba->mbx_cq->assoc_qid) {
				fpeq = eq;
				break;
			}
		}
	}
	if (!fpeq)
		return false;

	/* Turn off interrupts from this EQ */

	sli4_hba->sli4_eq_clr_intr(fpeq);

	/* Check to see if a mbox completion is pending */

	mbox_pending = lpfc_sli4_mbox_completions_pending(phba);

	/*
	 * If a mbox completion is pending, process all the events on EQ
	 * associated with the mbox completion queue (this could include
	 * mailbox commands, async events, els commands, receive queue data
	 * and fcp commands)
	 */

	if (mbox_pending)
		/* process and rearm the EQ */
		lpfc_sli4_process_eq(phba, fpeq);
	else
		/* Always clear and re-arm the EQ */
		sli4_hba->sli4_write_eq_db(phba, fpeq, 0, LPFC_QUEUE_REARM);

	return mbox_pending;

}