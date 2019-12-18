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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct lpfc_nvmet_tgtport {int /*<<< orphan*/  xmt_abort_rsp_error; int /*<<< orphan*/  xmt_abort_unsol; } ;
struct lpfc_nvmet_rcv_ctx {scalar_t__ state; int entry_cnt; int /*<<< orphan*/  hdwq; struct lpfc_iocbq* wqeq; int /*<<< orphan*/  oxid; } ;
struct lpfc_iocbq {int /*<<< orphan*/ * context3; int /*<<< orphan*/ * context2; int /*<<< orphan*/  iocb_flag; scalar_t__ iocb_cmpl; int /*<<< orphan*/  wqe_cmpl; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; TYPE_1__* targetport; } ;
struct TYPE_2__ {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_NVME_ABTS ; 
 int /*<<< orphan*/  LOG_NVME_IOERR ; 
 int /*<<< orphan*/  LPFC_IO_NVME_LS ; 
 void* LPFC_NVMET_STE_LS_ABORT ; 
 scalar_t__ LPFC_NVMET_STE_LS_RCV ; 
 scalar_t__ LPFC_NVMET_STE_LS_RSP ; 
 int WQE_BUSY ; 
 int WQE_SUCCESS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lpfc_nvmet_rcv_ctx*) ; 
 scalar_t__ lpfc_nvmet_unsol_issue_abort (struct lpfc_hba*,struct lpfc_nvmet_rcv_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_nvmet_xmt_ls_abort_cmp ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int lpfc_sli4_issue_wqe (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*) ; 
 struct lpfc_iocbq* lpfc_sli_get_iocbq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
lpfc_nvmet_unsol_ls_issue_abort(struct lpfc_hba *phba,
				struct lpfc_nvmet_rcv_ctx *ctxp,
				uint32_t sid, uint16_t xri)
{
	struct lpfc_nvmet_tgtport *tgtp;
	struct lpfc_iocbq *abts_wqeq;
	unsigned long flags;
	int rc;

	if ((ctxp->state == LPFC_NVMET_STE_LS_RCV && ctxp->entry_cnt == 1) ||
	    (ctxp->state == LPFC_NVMET_STE_LS_RSP && ctxp->entry_cnt == 2)) {
		ctxp->state = LPFC_NVMET_STE_LS_ABORT;
		ctxp->entry_cnt++;
	} else {
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
				"6418 NVMET LS abort state mismatch "
				"IO x%x: %d %d\n",
				ctxp->oxid, ctxp->state, ctxp->entry_cnt);
		ctxp->state = LPFC_NVMET_STE_LS_ABORT;
	}

	tgtp = (struct lpfc_nvmet_tgtport *)phba->targetport->private;
	if (!ctxp->wqeq) {
		/* Issue ABTS for this WQE based on iotag */
		ctxp->wqeq = lpfc_sli_get_iocbq(phba);
		if (!ctxp->wqeq) {
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME_ABTS,
					"6068 Abort failed: No wqeqs: "
					"xri: x%x\n", xri);
			/* No failure to an ABTS request. */
			kfree(ctxp);
			return 0;
		}
	}
	abts_wqeq = ctxp->wqeq;

	if (lpfc_nvmet_unsol_issue_abort(phba, ctxp, sid, xri) == 0) {
		rc = WQE_BUSY;
		goto out;
	}

	spin_lock_irqsave(&phba->hbalock, flags);
	abts_wqeq->wqe_cmpl = lpfc_nvmet_xmt_ls_abort_cmp;
	abts_wqeq->iocb_cmpl = 0;
	abts_wqeq->iocb_flag |=  LPFC_IO_NVME_LS;
	rc = lpfc_sli4_issue_wqe(phba, ctxp->hdwq, abts_wqeq);
	spin_unlock_irqrestore(&phba->hbalock, flags);
	if (rc == WQE_SUCCESS) {
		atomic_inc(&tgtp->xmt_abort_unsol);
		return 0;
	}
out:
	atomic_inc(&tgtp->xmt_abort_rsp_error);
	abts_wqeq->context2 = NULL;
	abts_wqeq->context3 = NULL;
	lpfc_sli_release_iocbq(phba, abts_wqeq);
	kfree(ctxp);
	lpfc_printf_log(phba, KERN_ERR, LOG_NVME_ABTS,
			"6056 Failed to Issue ABTS. Status x%x\n", rc);
	return 0;
}