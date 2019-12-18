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
struct lpfc_wcqe_complete {int /*<<< orphan*/  word3; int /*<<< orphan*/  total_data_placed; int /*<<< orphan*/  word0; int /*<<< orphan*/  parameter; } ;
struct lpfc_nvmet_tgtport {int /*<<< orphan*/  xmt_ls_abort_cmpl; } ;
struct lpfc_nvmet_rcv_ctx {scalar_t__ state; int /*<<< orphan*/  entry_cnt; int /*<<< orphan*/  oxid; } ;
struct lpfc_iocbq {int /*<<< orphan*/ * context3; struct lpfc_nvmet_rcv_ctx* context2; } ;
struct lpfc_hba {TYPE_1__* targetport; } ;
struct TYPE_2__ {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_ABTS ; 
 int /*<<< orphan*/  LOG_NVME_IOERR ; 
 scalar_t__ LPFC_NVMET_STE_LS_ABORT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lpfc_nvmet_rcv_ctx*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct lpfc_nvmet_rcv_ctx*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 

__attribute__((used)) static void
lpfc_nvmet_xmt_ls_abort_cmp(struct lpfc_hba *phba, struct lpfc_iocbq *cmdwqe,
			    struct lpfc_wcqe_complete *wcqe)
{
	struct lpfc_nvmet_rcv_ctx *ctxp;
	struct lpfc_nvmet_tgtport *tgtp;
	uint32_t result;

	ctxp = cmdwqe->context2;
	result = wcqe->parameter;

	tgtp = (struct lpfc_nvmet_tgtport *)phba->targetport->private;
	atomic_inc(&tgtp->xmt_ls_abort_cmpl);

	lpfc_printf_log(phba, KERN_INFO, LOG_NVME_ABTS,
			"6083 Abort cmpl: ctx x%px WCQE:%08x %08x %08x %08x\n",
			ctxp, wcqe->word0, wcqe->total_data_placed,
			result, wcqe->word3);

	if (!ctxp) {
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_ABTS,
				"6415 NVMET LS Abort No ctx: WCQE: "
				 "%08x %08x %08x %08x\n",
				wcqe->word0, wcqe->total_data_placed,
				result, wcqe->word3);

		lpfc_sli_release_iocbq(phba, cmdwqe);
		return;
	}

	if (ctxp->state != LPFC_NVMET_STE_LS_ABORT) {
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
				"6416 NVMET LS abort cmpl state mismatch: "
				"oxid x%x: %d %d\n",
				ctxp->oxid, ctxp->state, ctxp->entry_cnt);
	}

	cmdwqe->context2 = NULL;
	cmdwqe->context3 = NULL;
	lpfc_sli_release_iocbq(phba, cmdwqe);
	kfree(ctxp);
}