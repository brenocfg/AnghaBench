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
struct lpfc_queue {int max_proc_limit; int notify_interval; int CQ_max_cqe; scalar_t__ queue_claimed; int /*<<< orphan*/  queue_id; TYPE_1__* assoc_qp; int /*<<< orphan*/  q_flag; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sli4_write_cq_db ) (struct lpfc_hba*,struct lpfc_queue*,int,int /*<<< orphan*/ ) ;} ;
struct lpfc_hba {int cfg_cq_poll_threshold; TYPE_2__ sli4_hba; } ;
typedef  struct lpfc_cqe lpfc_cqe ;
struct TYPE_3__ {int EQ_cqe_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBA_NVMET_CQ_NOTIFY ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int LPFC_NVMET_CQ_NOTIFY ; 
 int /*<<< orphan*/  LPFC_QUEUE_NOARM ; 
 int /*<<< orphan*/  LPFC_QUEUE_REARM ; 
 int /*<<< orphan*/  __lpfc_sli4_consume_cqe (struct lpfc_hba*,struct lpfc_queue*,struct lpfc_cqe*) ; 
 scalar_t__ cmpxchg (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct lpfc_cqe* lpfc_sli4_cq_get (struct lpfc_queue*) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct lpfc_hba*,struct lpfc_queue*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
__lpfc_sli4_process_cq(struct lpfc_hba *phba, struct lpfc_queue *cq,
	bool (*handler)(struct lpfc_hba *, struct lpfc_queue *,
			struct lpfc_cqe *), unsigned long *delay)
{
	struct lpfc_cqe *cqe;
	bool workposted = false;
	int count = 0, consumed = 0;
	bool arm = true;

	/* default - no reschedule */
	*delay = 0;

	if (cmpxchg(&cq->queue_claimed, 0, 1) != 0)
		goto rearm_and_exit;

	/* Process all the entries to the CQ */
	cq->q_flag = 0;
	cqe = lpfc_sli4_cq_get(cq);
	while (cqe) {
		workposted |= handler(phba, cq, cqe);
		__lpfc_sli4_consume_cqe(phba, cq, cqe);

		consumed++;
		if (!(++count % cq->max_proc_limit))
			break;

		if (!(count % cq->notify_interval)) {
			phba->sli4_hba.sli4_write_cq_db(phba, cq, consumed,
						LPFC_QUEUE_NOARM);
			consumed = 0;
		}

		if (count == LPFC_NVMET_CQ_NOTIFY)
			cq->q_flag |= HBA_NVMET_CQ_NOTIFY;

		cqe = lpfc_sli4_cq_get(cq);
	}
	if (count >= phba->cfg_cq_poll_threshold) {
		*delay = 1;
		arm = false;
	}

	/* Track the max number of CQEs processed in 1 EQ */
	if (count > cq->CQ_max_cqe)
		cq->CQ_max_cqe = count;

	cq->assoc_qp->EQ_cqe_cnt += count;

	/* Catch the no cq entry condition */
	if (unlikely(count == 0))
		lpfc_printf_log(phba, KERN_INFO, LOG_SLI,
				"0369 No entry from completion queue "
				"qid=%d\n", cq->queue_id);

	cq->queue_claimed = 0;

rearm_and_exit:
	phba->sli4_hba.sli4_write_cq_db(phba, cq, consumed,
			arm ?  LPFC_QUEUE_REARM : LPFC_QUEUE_NOARM);

	return workposted;
}