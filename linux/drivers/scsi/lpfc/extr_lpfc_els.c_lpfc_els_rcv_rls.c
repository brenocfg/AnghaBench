#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ vendorUnique; int /*<<< orphan*/  lsRjtRsnCodeExp; int /*<<< orphan*/  lsRjtRsnCode; scalar_t__ lsRjtRsvd0; } ;
struct TYPE_15__ {int /*<<< orphan*/  lsRjtError; TYPE_4__ b; } ;
struct ls_rjt {TYPE_5__ un; } ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; } ;
struct TYPE_11__ {int ox_id; } ;
struct TYPE_12__ {TYPE_1__ rcvsli3; } ;
struct TYPE_13__ {int ulpContext; TYPE_2__ unsli3; } ;
struct lpfc_iocbq {TYPE_3__ iocb; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct TYPE_16__ {int /*<<< orphan*/  mbox_cmpl; struct lpfc_vport* vport; int /*<<< orphan*/  ctx_ndlp; void* ctx_buf; } ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LSEXP_CANT_GIVE_DATA ; 
 int /*<<< orphan*/  LSRJT_UNABLE_TPC ; 
 scalar_t__ MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 scalar_t__ NLP_STE_MAPPED_NODE ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 int /*<<< orphan*/  lpfc_els_rsp_reject (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_els_rsp_rls_acc ; 
 int /*<<< orphan*/  lpfc_nlp_get (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_read_lnk_stat (struct lpfc_hba*,TYPE_6__*) ; 
 scalar_t__ lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_els_rcv_rls(struct lpfc_vport *vport, struct lpfc_iocbq *cmdiocb,
		 struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba *phba = vport->phba;
	LPFC_MBOXQ_t *mbox;
	struct ls_rjt stat;

	if ((ndlp->nlp_state != NLP_STE_UNMAPPED_NODE) &&
	    (ndlp->nlp_state != NLP_STE_MAPPED_NODE))
		/* reject the unsolicited RPS request and done with it */
		goto reject_out;

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_ATOMIC);
	if (mbox) {
		lpfc_read_lnk_stat(phba, mbox);
		mbox->ctx_buf = (void *)((unsigned long)
			((cmdiocb->iocb.unsli3.rcvsli3.ox_id << 16) |
			cmdiocb->iocb.ulpContext)); /* rx_id */
		mbox->ctx_ndlp = lpfc_nlp_get(ndlp);
		mbox->vport = vport;
		mbox->mbox_cmpl = lpfc_els_rsp_rls_acc;
		if (lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT)
			!= MBX_NOT_FINISHED)
			/* Mbox completion will send ELS Response */
			return 0;
		/* Decrement reference count used for the failed mbox
		 * command.
		 */
		lpfc_nlp_put(ndlp);
		mempool_free(mbox, phba->mbox_mem_pool);
	}
reject_out:
	/* issue rejection response */
	stat.un.b.lsRjtRsvd0 = 0;
	stat.un.b.lsRjtRsnCode = LSRJT_UNABLE_TPC;
	stat.un.b.lsRjtRsnCodeExp = LSEXP_CANT_GIVE_DATA;
	stat.un.b.vendorUnique = 0;
	lpfc_els_rsp_reject(vport, stat.un.lsRjtError, cmdiocb, ndlp, NULL);
	return 0;
}