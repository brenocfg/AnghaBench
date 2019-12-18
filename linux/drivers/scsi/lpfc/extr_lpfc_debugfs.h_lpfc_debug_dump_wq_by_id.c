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
struct TYPE_5__ {TYPE_3__* nvmels_wq; TYPE_3__* els_wq; TYPE_1__* hdwq; } ;
struct lpfc_hba {int cfg_hdw_queue; TYPE_2__ sli4_hba; } ;
struct TYPE_6__ {int queue_id; } ;
struct TYPE_4__ {TYPE_3__* io_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_debug_dump_q (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static inline void
lpfc_debug_dump_wq_by_id(struct lpfc_hba *phba, int qid)
{
	int wq_idx;

	for (wq_idx = 0; wq_idx < phba->cfg_hdw_queue; wq_idx++)
		if (phba->sli4_hba.hdwq[wq_idx].io_wq->queue_id == qid)
			break;
	if (wq_idx < phba->cfg_hdw_queue) {
		pr_err("IO WQ[Idx:%d|Qid:%d]\n", wq_idx, qid);
		lpfc_debug_dump_q(phba->sli4_hba.hdwq[wq_idx].io_wq);
		return;
	}

	if (phba->sli4_hba.els_wq->queue_id == qid) {
		pr_err("ELS WQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.els_wq);
		return;
	}

	if (phba->sli4_hba.nvmels_wq->queue_id == qid) {
		pr_err("NVME LS WQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.nvmels_wq);
	}
}