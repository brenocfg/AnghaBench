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
typedef  size_t uint16_t ;
struct lpfc_queue {size_t hdwq; size_t queue_id; int /*<<< orphan*/  irqwork; int /*<<< orphan*/  chann; scalar_t__ isr_timestamp; } ;
struct TYPE_4__ {size_t cq_max; TYPE_1__* hdwq; struct lpfc_queue* nvmels_cq; struct lpfc_queue** nvmet_cqset; struct lpfc_queue** cq_lookup; } ;
struct lpfc_hba {size_t cfg_nvmet_mrq; int /*<<< orphan*/  wq; scalar_t__ ktime_on; TYPE_2__ sli4_hba; } ;
struct lpfc_eqe {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hba_eq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ bf_get_le32 (int /*<<< orphan*/ ,struct lpfc_eqe*) ; 
 scalar_t__ ktime_get_ns () ; 
 int /*<<< orphan*/  lpfc_eqe_major_code ; 
 int /*<<< orphan*/  lpfc_eqe_minor_code ; 
 int /*<<< orphan*/  lpfc_eqe_resource_id ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t,...) ; 
 int /*<<< orphan*/  lpfc_sli4_sp_handle_eqe (struct lpfc_hba*,struct lpfc_eqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
lpfc_sli4_hba_handle_eqe(struct lpfc_hba *phba, struct lpfc_queue *eq,
			 struct lpfc_eqe *eqe)
{
	struct lpfc_queue *cq = NULL;
	uint32_t qidx = eq->hdwq;
	uint16_t cqid, id;

	if (unlikely(bf_get_le32(lpfc_eqe_major_code, eqe) != 0)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0366 Not a valid completion "
				"event: majorcode=x%x, minorcode=x%x\n",
				bf_get_le32(lpfc_eqe_major_code, eqe),
				bf_get_le32(lpfc_eqe_minor_code, eqe));
		return;
	}

	/* Get the reference to the corresponding CQ */
	cqid = bf_get_le32(lpfc_eqe_resource_id, eqe);

	/* Use the fast lookup method first */
	if (cqid <= phba->sli4_hba.cq_max) {
		cq = phba->sli4_hba.cq_lookup[cqid];
		if (cq)
			goto  work_cq;
	}

	/* Next check for NVMET completion */
	if (phba->cfg_nvmet_mrq && phba->sli4_hba.nvmet_cqset) {
		id = phba->sli4_hba.nvmet_cqset[0]->queue_id;
		if ((cqid >= id) && (cqid < (id + phba->cfg_nvmet_mrq))) {
			/* Process NVMET unsol rcv */
			cq = phba->sli4_hba.nvmet_cqset[cqid - id];
			goto  process_cq;
		}
	}

	if (phba->sli4_hba.nvmels_cq &&
	    (cqid == phba->sli4_hba.nvmels_cq->queue_id)) {
		/* Process NVME unsol rcv */
		cq = phba->sli4_hba.nvmels_cq;
	}

	/* Otherwise this is a Slow path event */
	if (cq == NULL) {
		lpfc_sli4_sp_handle_eqe(phba, eqe,
					phba->sli4_hba.hdwq[qidx].hba_eq);
		return;
	}

process_cq:
	if (unlikely(cqid != cq->queue_id)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0368 Miss-matched fast-path completion "
				"queue identifier: eqcqid=%d, fcpcqid=%d\n",
				cqid, cq->queue_id);
		return;
	}

work_cq:
#if defined(CONFIG_SCSI_LPFC_DEBUG_FS)
	if (phba->ktime_on)
		cq->isr_timestamp = ktime_get_ns();
	else
		cq->isr_timestamp = 0;
#endif
	if (!queue_work_on(cq->chann, phba->wq, &cq->irqwork))
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0363 Cannot schedule soft IRQ "
				"for CQ eqcqid=%d, cqid=%d on CPU %d\n",
				cqid, cq->queue_id, raw_smp_processor_id());
}