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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct lpfc_queue {int hba_index; int qe_valid; int entry_count; } ;
struct lpfc_mcqe {int dummy; } ;
struct TYPE_3__ {scalar_t__ cqav; } ;
struct TYPE_4__ {TYPE_1__ pc_sli4_params; struct lpfc_queue* mbx_cq; } ;
struct lpfc_hba {scalar_t__ sli_rev; TYPE_2__ sli4_hba; } ;
typedef  struct lpfc_mcqe lpfc_cqe ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 
 int bf_get_le32 (int /*<<< orphan*/ ,struct lpfc_mcqe*) ; 
 int /*<<< orphan*/  lpfc_cqe_valid ; 
 scalar_t__ lpfc_sli4_qe (struct lpfc_queue*,int) ; 
 int /*<<< orphan*/  lpfc_trailer_async ; 
 int /*<<< orphan*/  lpfc_trailer_completed ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
lpfc_sli4_mbox_completions_pending(struct lpfc_hba *phba)
{

	uint32_t idx;
	struct lpfc_queue *mcq;
	struct lpfc_mcqe *mcqe;
	bool pending_completions = false;
	uint8_t	qe_valid;

	if (unlikely(!phba) || (phba->sli_rev != LPFC_SLI_REV4))
		return false;

	/* Check for completions on mailbox completion queue */

	mcq = phba->sli4_hba.mbx_cq;
	idx = mcq->hba_index;
	qe_valid = mcq->qe_valid;
	while (bf_get_le32(lpfc_cqe_valid,
	       (struct lpfc_cqe *)lpfc_sli4_qe(mcq, idx)) == qe_valid) {
		mcqe = (struct lpfc_mcqe *)(lpfc_sli4_qe(mcq, idx));
		if (bf_get_le32(lpfc_trailer_completed, mcqe) &&
		    (!bf_get_le32(lpfc_trailer_async, mcqe))) {
			pending_completions = true;
			break;
		}
		idx = (idx + 1) % mcq->entry_count;
		if (mcq->hba_index == idx)
			break;

		/* if the index wrapped around, toggle the valid bit */
		if (phba->sli4_hba.pc_sli4_params.cqav && !idx)
			qe_valid = (qe_valid) ? 0 : 1;
	}
	return pending_completions;

}