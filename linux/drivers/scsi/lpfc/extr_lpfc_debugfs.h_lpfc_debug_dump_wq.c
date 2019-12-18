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
struct lpfc_queue {int /*<<< orphan*/  queue_id; } ;
struct TYPE_3__ {struct lpfc_queue* nvmels_wq; struct lpfc_queue* els_wq; struct lpfc_queue* mbx_wq; TYPE_2__* hdwq; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;
struct TYPE_4__ {struct lpfc_queue* io_wq; } ;

/* Variables and functions */
 int DUMP_ELS ; 
 int DUMP_IO ; 
 int DUMP_MBX ; 
 int DUMP_NVMELS ; 
 int /*<<< orphan*/  lpfc_debug_dump_q (struct lpfc_queue*) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int,...) ; 

__attribute__((used)) static inline void
lpfc_debug_dump_wq(struct lpfc_hba *phba, int qtype, int wqidx)
{
	struct lpfc_queue *wq;
	char *qtypestr;

	if (qtype == DUMP_IO) {
		wq = phba->sli4_hba.hdwq[wqidx].io_wq;
		qtypestr = "IO";
	} else if (qtype == DUMP_MBX) {
		wq = phba->sli4_hba.mbx_wq;
		qtypestr = "MBX";
	} else if (qtype == DUMP_ELS) {
		wq = phba->sli4_hba.els_wq;
		qtypestr = "ELS";
	} else if (qtype == DUMP_NVMELS) {
		wq = phba->sli4_hba.nvmels_wq;
		qtypestr = "NVMELS";
	} else
		return;

	if (qtype == DUMP_IO)
		pr_err("%s WQ: WQ[Idx:%d|Qid:%d]\n",
			qtypestr, wqidx, wq->queue_id);
	else
		pr_err("%s WQ: WQ[Qid:%d]\n",
			qtypestr, wq->queue_id);

	lpfc_debug_dump_q(wq);
}