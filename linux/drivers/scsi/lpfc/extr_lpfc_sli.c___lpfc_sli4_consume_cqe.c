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
struct lpfc_queue {int host_index; int entry_count; int qe_valid; } ;
struct TYPE_4__ {scalar_t__ cqav; } ;
struct TYPE_3__ {TYPE_2__ pc_sli4_params; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;
struct lpfc_cqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bf_set_le32 (int /*<<< orphan*/ ,struct lpfc_cqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cqe_valid ; 

__attribute__((used)) static void
__lpfc_sli4_consume_cqe(struct lpfc_hba *phba, struct lpfc_queue *cq,
			struct lpfc_cqe *cqe)
{
	if (!phba->sli4_hba.pc_sli4_params.cqav)
		bf_set_le32(lpfc_cqe_valid, cqe, 0);

	cq->host_index = ((cq->host_index + 1) % cq->entry_count);

	/* if the index wrapped around, toggle the valid bit */
	if (phba->sli4_hba.pc_sli4_params.cqav && !cq->host_index)
		cq->qe_valid = (cq->qe_valid) ? 0 : 1;
}