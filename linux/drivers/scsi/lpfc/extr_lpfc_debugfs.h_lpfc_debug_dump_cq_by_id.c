#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* mbx_cq; TYPE_3__* nvmels_cq; TYPE_3__* els_cq; TYPE_1__* hdwq; } ;
struct lpfc_hba {int cfg_hdw_queue; TYPE_2__ sli4_hba; } ;
struct TYPE_6__ {int queue_id; } ;
struct TYPE_4__ {TYPE_3__* io_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_debug_dump_q (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static inline void
lpfc_debug_dump_cq_by_id(struct lpfc_hba *phba, int qid)
{
	int cq_idx;

	for (cq_idx = 0; cq_idx < phba->cfg_hdw_queue; cq_idx++)
		if (phba->sli4_hba.hdwq[cq_idx].io_cq->queue_id == qid)
			break;

	if (cq_idx < phba->cfg_hdw_queue) {
		pr_err("IO CQ[Idx:%d|Qid:%d]\n", cq_idx, qid);
		lpfc_debug_dump_q(phba->sli4_hba.hdwq[cq_idx].io_cq);
		return;
	}

	if (phba->sli4_hba.els_cq->queue_id == qid) {
		pr_err("ELS CQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.els_cq);
		return;
	}

	if (phba->sli4_hba.nvmels_cq->queue_id == qid) {
		pr_err("NVME LS CQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.nvmels_cq);
		return;
	}

	if (phba->sli4_hba.mbx_cq->queue_id == qid) {
		pr_err("MBX CQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.mbx_cq);
	}
}