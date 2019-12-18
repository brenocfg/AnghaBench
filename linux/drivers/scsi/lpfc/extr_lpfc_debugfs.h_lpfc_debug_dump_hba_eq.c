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
struct TYPE_4__ {TYPE_1__* hdwq; } ;
struct lpfc_hba {TYPE_2__ sli4_hba; } ;
struct TYPE_3__ {struct lpfc_queue* hba_eq; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_debug_dump_q (struct lpfc_queue*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lpfc_debug_dump_hba_eq(struct lpfc_hba *phba, int qidx)
{
	struct lpfc_queue *qp;

	qp = phba->sli4_hba.hdwq[qidx].hba_eq;

	pr_err("EQ[Idx:%d|Qid:%d]\n", qidx, qp->queue_id);

	lpfc_debug_dump_q(qp);
}