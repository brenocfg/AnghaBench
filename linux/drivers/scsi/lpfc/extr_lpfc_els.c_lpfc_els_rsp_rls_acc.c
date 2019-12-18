#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_rpi; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  vport; } ;
struct TYPE_13__ {void* ox_id; } ;
struct TYPE_14__ {TYPE_2__ rcvsli3; } ;
struct TYPE_20__ {void* ulpContext; TYPE_3__ unsli3; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iocb_cmpl; TYPE_9__ iocb; int /*<<< orphan*/  iotag; scalar_t__ context2; } ;
struct TYPE_17__ {int /*<<< orphan*/  elsXmitACC; } ;
struct lpfc_hba {TYPE_6__ fc_stat; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  pport; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct RLS_RSP {void* crcCnt; void* invalidXmitWord; void* primSeqErrCnt; void* lossSignalCnt; void* lossSyncCnt; void* linkFailureCnt; } ;
struct TYPE_15__ {int /*<<< orphan*/  crcCnt; int /*<<< orphan*/  invalidXmitWord; int /*<<< orphan*/  primSeqErrCnt; int /*<<< orphan*/  lossSignalCnt; int /*<<< orphan*/  lossSyncCnt; int /*<<< orphan*/  linkFailureCnt; } ;
struct TYPE_16__ {TYPE_4__ varRdLnk; } ;
struct TYPE_18__ {TYPE_5__ un; scalar_t__ mbxStatus; } ;
struct TYPE_12__ {TYPE_7__ mb; } ;
struct TYPE_19__ {int /*<<< orphan*/ * ctx_ndlp; int /*<<< orphan*/ * ctx_buf; TYPE_1__ u; } ;
typedef  TYPE_7__ MAILBOX_t ;
typedef  TYPE_8__ LPFC_MBOXQ_t ;
typedef  TYPE_9__ IOCB_t ;

/* Variables and functions */
 int ELS_CMD_ACC ; 
 scalar_t__ IOCB_ERROR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cmpl_els_rsp ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_max_els_tries ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_8__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_els_rsp_rls_acc(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb;
	IOCB_t *icmd;
	struct RLS_RSP *rls_rsp;
	uint8_t *pcmd;
	struct lpfc_iocbq *elsiocb;
	struct lpfc_nodelist *ndlp;
	uint16_t oxid;
	uint16_t rxid;
	uint32_t cmdsize;

	mb = &pmb->u.mb;

	ndlp = (struct lpfc_nodelist *)pmb->ctx_ndlp;
	rxid = (uint16_t)((unsigned long)(pmb->ctx_buf) & 0xffff);
	oxid = (uint16_t)(((unsigned long)(pmb->ctx_buf) >> 16) & 0xffff);
	pmb->ctx_buf = NULL;
	pmb->ctx_ndlp = NULL;

	if (mb->mbxStatus) {
		mempool_free(pmb, phba->mbox_mem_pool);
		return;
	}

	cmdsize = sizeof(struct RLS_RSP) + sizeof(uint32_t);
	elsiocb = lpfc_prep_els_iocb(phba->pport, 0, cmdsize,
				     lpfc_max_els_tries, ndlp,
				     ndlp->nlp_DID, ELS_CMD_ACC);

	/* Decrement the ndlp reference count from previous mbox command */
	lpfc_nlp_put(ndlp);

	if (!elsiocb) {
		mempool_free(pmb, phba->mbox_mem_pool);
		return;
	}

	icmd = &elsiocb->iocb;
	icmd->ulpContext = rxid;
	icmd->unsli3.rcvsli3.ox_id = oxid;

	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) elsiocb->context2)->virt);
	*((uint32_t *) (pcmd)) = ELS_CMD_ACC;
	pcmd += sizeof(uint32_t); /* Skip past command */
	rls_rsp = (struct RLS_RSP *)pcmd;

	rls_rsp->linkFailureCnt = cpu_to_be32(mb->un.varRdLnk.linkFailureCnt);
	rls_rsp->lossSyncCnt = cpu_to_be32(mb->un.varRdLnk.lossSyncCnt);
	rls_rsp->lossSignalCnt = cpu_to_be32(mb->un.varRdLnk.lossSignalCnt);
	rls_rsp->primSeqErrCnt = cpu_to_be32(mb->un.varRdLnk.primSeqErrCnt);
	rls_rsp->invalidXmitWord = cpu_to_be32(mb->un.varRdLnk.invalidXmitWord);
	rls_rsp->crcCnt = cpu_to_be32(mb->un.varRdLnk.crcCnt);
	mempool_free(pmb, phba->mbox_mem_pool);
	/* Xmit ELS RLS ACC response tag <ulpIoTag> */
	lpfc_printf_vlog(ndlp->vport, KERN_INFO, LOG_ELS,
			 "2874 Xmit ELS RLS ACC response tag x%x xri x%x, "
			 "did x%x, nlp_flag x%x, nlp_state x%x, rpi x%x\n",
			 elsiocb->iotag, elsiocb->iocb.ulpContext,
			 ndlp->nlp_DID, ndlp->nlp_flag, ndlp->nlp_state,
			 ndlp->nlp_rpi);
	elsiocb->iocb_cmpl = lpfc_cmpl_els_rsp;
	phba->fc_stat.elsXmitACC++;
	if (lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0) == IOCB_ERROR)
		lpfc_els_free_iocb(phba, elsiocb);
}