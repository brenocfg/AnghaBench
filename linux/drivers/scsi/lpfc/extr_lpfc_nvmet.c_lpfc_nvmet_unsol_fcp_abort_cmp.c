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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_wcqe_complete {int /*<<< orphan*/  word3; int /*<<< orphan*/  total_data_placed; int /*<<< orphan*/  word0; int /*<<< orphan*/  parameter; } ;
struct lpfc_nvmet_tgtport {int /*<<< orphan*/  xmt_abort_rsp; int /*<<< orphan*/  xmt_fcp_abort_cmpl; } ;
struct lpfc_nvmet_rcv_ctx {int flag; scalar_t__ state; int /*<<< orphan*/  ctxbuf; int /*<<< orphan*/  oxid; int /*<<< orphan*/  ctxlock; int /*<<< orphan*/  list; } ;
struct lpfc_iocbq {int /*<<< orphan*/ * context3; struct lpfc_nvmet_rcv_ctx* context2; } ;
struct TYPE_4__ {int /*<<< orphan*/  abts_nvmet_buf_list_lock; } ;
struct lpfc_hba {TYPE_2__ sli4_hba; TYPE_1__* targetport; } ;
struct TYPE_3__ {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_ABTS ; 
 int LPFC_NVMET_ABORT_OP ; 
 int LPFC_NVMET_CTX_RLS ; 
 scalar_t__ LPFC_NVMET_STE_ABORT ; 
 scalar_t__ LPFC_NVMET_STE_DONE ; 
 int LPFC_NVMET_XBUSY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_nvmet_ctxbuf_post (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lpfc_nvmet_unsol_fcp_abort_cmp(struct lpfc_hba *phba, struct lpfc_iocbq *cmdwqe,
			       struct lpfc_wcqe_complete *wcqe)
{
	struct lpfc_nvmet_rcv_ctx *ctxp;
	struct lpfc_nvmet_tgtport *tgtp;
	unsigned long flags;
	uint32_t result;
	bool released = false;

	ctxp = cmdwqe->context2;
	result = wcqe->parameter;

	if (!ctxp) {
		/* if context is clear, related io alrady complete */
		lpfc_printf_log(phba, KERN_INFO, LOG_NVME_ABTS,
				"6070 ABTS cmpl: WCQE: %08x %08x %08x %08x\n",
				wcqe->word0, wcqe->total_data_placed,
				result, wcqe->word3);
		return;
	}

	tgtp = (struct lpfc_nvmet_tgtport *)phba->targetport->private;
	spin_lock_irqsave(&ctxp->ctxlock, flags);
	if (ctxp->flag & LPFC_NVMET_ABORT_OP)
		atomic_inc(&tgtp->xmt_fcp_abort_cmpl);

	/* Sanity check */
	if (ctxp->state != LPFC_NVMET_STE_ABORT) {
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_ABTS,
				"6112 ABTS Wrong state:%d oxid x%x\n",
				ctxp->state, ctxp->oxid);
	}

	/* Check if we already received a free context call
	 * and we have completed processing an abort situation.
	 */
	ctxp->state = LPFC_NVMET_STE_DONE;
	if ((ctxp->flag & LPFC_NVMET_CTX_RLS) &&
	    !(ctxp->flag & LPFC_NVMET_XBUSY)) {
		spin_lock(&phba->sli4_hba.abts_nvmet_buf_list_lock);
		list_del_init(&ctxp->list);
		spin_unlock(&phba->sli4_hba.abts_nvmet_buf_list_lock);
		released = true;
	}
	ctxp->flag &= ~LPFC_NVMET_ABORT_OP;
	spin_unlock_irqrestore(&ctxp->ctxlock, flags);
	atomic_inc(&tgtp->xmt_abort_rsp);

	lpfc_printf_log(phba, KERN_INFO, LOG_NVME_ABTS,
			"6316 ABTS cmpl oxid x%x flg x%x (%x) "
			"WCQE: %08x %08x %08x %08x\n",
			ctxp->oxid, ctxp->flag, released,
			wcqe->word0, wcqe->total_data_placed,
			result, wcqe->word3);

	cmdwqe->context2 = NULL;
	cmdwqe->context3 = NULL;
	/*
	 * if transport has released ctx, then can reuse it. Otherwise,
	 * will be recycled by transport release call.
	 */
	if (released)
		lpfc_nvmet_ctxbuf_post(phba, ctxp->ctxbuf);

	/* Since iaab/iaar are NOT set, there is no work left.
	 * For LPFC_NVMET_XBUSY, lpfc_sli4_nvmet_xri_aborted
	 * should have been called already.
	 */
}