#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lpfc_wcqe_complete {int parameter; int /*<<< orphan*/  word3; int /*<<< orphan*/  total_data_placed; int /*<<< orphan*/  word0; } ;
struct TYPE_2__ {int /*<<< orphan*/  iocb_event; } ;
struct lpfc_sli_ring {int /*<<< orphan*/  ring_lock; TYPE_1__ stats; } ;
struct lpfc_queue {int /*<<< orphan*/  isr_timestamp; struct lpfc_sli_ring* pring; } ;
struct lpfc_iocbq {int iocb_flag; int /*<<< orphan*/  (* iocb_cmpl ) (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ;int /*<<< orphan*/  (* wqe_cmpl ) (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_wcqe_complete*) ;int /*<<< orphan*/  isr_timestamp; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  (* lpfc_rampdown_queue_depth ) (struct lpfc_hba*) ;} ;

/* Variables and functions */
 int IOERR_NO_RESOURCES ; 
 int IOERR_PARAM_MASK ; 
 scalar_t__ IOSTAT_LOCAL_REJECT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int LPFC_DRIVER_ABORTED ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct lpfc_wcqe_complete*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  lpfc_sli4_iocb_param_transfer (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*,struct lpfc_wcqe_complete*) ; 
 struct lpfc_iocbq* lpfc_sli_iocbq_lookup_by_tag (struct lpfc_hba*,struct lpfc_sli_ring*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_wcqe_c_request_tag ; 
 int /*<<< orphan*/  lpfc_wcqe_c_status ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*) ; 
 int /*<<< orphan*/  stub2 (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_wcqe_complete*) ; 
 int /*<<< orphan*/  stub3 (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
lpfc_sli4_fp_handle_fcp_wcqe(struct lpfc_hba *phba, struct lpfc_queue *cq,
			     struct lpfc_wcqe_complete *wcqe)
{
	struct lpfc_sli_ring *pring = cq->pring;
	struct lpfc_iocbq *cmdiocbq;
	struct lpfc_iocbq irspiocbq;
	unsigned long iflags;

	/* Check for response status */
	if (unlikely(bf_get(lpfc_wcqe_c_status, wcqe))) {
		/* If resource errors reported from HBA, reduce queue
		 * depth of the SCSI device.
		 */
		if (((bf_get(lpfc_wcqe_c_status, wcqe) ==
		     IOSTAT_LOCAL_REJECT)) &&
		    ((wcqe->parameter & IOERR_PARAM_MASK) ==
		     IOERR_NO_RESOURCES))
			phba->lpfc_rampdown_queue_depth(phba);

		/* Log the error status */
		lpfc_printf_log(phba, KERN_INFO, LOG_SLI,
				"0373 FCP CQE error: status=x%x: "
				"CQE: %08x %08x %08x %08x\n",
				bf_get(lpfc_wcqe_c_status, wcqe),
				wcqe->word0, wcqe->total_data_placed,
				wcqe->parameter, wcqe->word3);
	}

	/* Look up the FCP command IOCB and create pseudo response IOCB */
	spin_lock_irqsave(&pring->ring_lock, iflags);
	pring->stats.iocb_event++;
	spin_unlock_irqrestore(&pring->ring_lock, iflags);
	cmdiocbq = lpfc_sli_iocbq_lookup_by_tag(phba, pring,
				bf_get(lpfc_wcqe_c_request_tag, wcqe));
	if (unlikely(!cmdiocbq)) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_SLI,
				"0374 FCP complete with no corresponding "
				"cmdiocb: iotag (%d)\n",
				bf_get(lpfc_wcqe_c_request_tag, wcqe));
		return;
	}
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	cmdiocbq->isr_timestamp = cq->isr_timestamp;
#endif
	if (cmdiocbq->iocb_cmpl == NULL) {
		if (cmdiocbq->wqe_cmpl) {
			if (cmdiocbq->iocb_flag & LPFC_DRIVER_ABORTED) {
				spin_lock_irqsave(&phba->hbalock, iflags);
				cmdiocbq->iocb_flag &= ~LPFC_DRIVER_ABORTED;
				spin_unlock_irqrestore(&phba->hbalock, iflags);
			}

			/* Pass the cmd_iocb and the wcqe to the upper layer */
			(cmdiocbq->wqe_cmpl)(phba, cmdiocbq, wcqe);
			return;
		}
		lpfc_printf_log(phba, KERN_WARNING, LOG_SLI,
				"0375 FCP cmdiocb not callback function "
				"iotag: (%d)\n",
				bf_get(lpfc_wcqe_c_request_tag, wcqe));
		return;
	}

	/* Fake the irspiocb and copy necessary response information */
	lpfc_sli4_iocb_param_transfer(phba, &irspiocbq, cmdiocbq, wcqe);

	if (cmdiocbq->iocb_flag & LPFC_DRIVER_ABORTED) {
		spin_lock_irqsave(&phba->hbalock, iflags);
		cmdiocbq->iocb_flag &= ~LPFC_DRIVER_ABORTED;
		spin_unlock_irqrestore(&phba->hbalock, iflags);
	}

	/* Pass the cmd_iocb and the rsp state to the upper layer */
	(cmdiocbq->iocb_cmpl)(phba, cmdiocbq, &irspiocbq);
}