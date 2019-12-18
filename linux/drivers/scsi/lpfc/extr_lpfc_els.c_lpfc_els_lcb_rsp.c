#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
union lpfc_sli4_cfg_shdr {int /*<<< orphan*/  response; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_27__ {int /*<<< orphan*/  lsRjtRsnCodeExp; int /*<<< orphan*/  lsRjtRsnCode; } ;
struct TYPE_28__ {TYPE_8__ b; } ;
struct ls_rjt {TYPE_9__ un; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_lcb_context {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  rx_id; int /*<<< orphan*/  duration; int /*<<< orphan*/  frequency; int /*<<< orphan*/  capability; int /*<<< orphan*/  type; int /*<<< orphan*/  sub_command; struct lpfc_nodelist* ndlp; } ;
struct TYPE_25__ {int /*<<< orphan*/  ox_id; } ;
struct TYPE_26__ {TYPE_6__ rcvsli3; } ;
struct TYPE_19__ {TYPE_7__ unsli3; int /*<<< orphan*/  ulpContext; } ;
struct lpfc_iocbq {void* iocb_cmpl; scalar_t__ context2; TYPE_13__ iocb; } ;
struct TYPE_16__ {int /*<<< orphan*/  elsXmitLSRJT; int /*<<< orphan*/  elsXmitACC; } ;
struct lpfc_hba {TYPE_10__ fc_stat; int /*<<< orphan*/  pport; int /*<<< orphan*/  mbox_mem_pool; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct fc_lcb_res_frame {int /*<<< orphan*/  lcb_duration; int /*<<< orphan*/  lcb_frequency; int /*<<< orphan*/  capability; int /*<<< orphan*/  lcb_type; int /*<<< orphan*/  lcb_sub_command; } ;
struct TYPE_20__ {int /*<<< orphan*/  cfg_shdr; } ;
struct TYPE_21__ {TYPE_1__ header; } ;
struct TYPE_22__ {TYPE_2__ beacon_config; } ;
struct TYPE_23__ {TYPE_3__ un; } ;
struct TYPE_17__ {scalar_t__ mbxStatus; } ;
struct TYPE_24__ {TYPE_4__ mqe; TYPE_11__ mb; } ;
struct TYPE_18__ {TYPE_5__ u; int /*<<< orphan*/ * ctx_buf; int /*<<< orphan*/ * ctx_ndlp; } ;
typedef  TYPE_11__ MAILBOX_t ;
typedef  TYPE_12__ LPFC_MBOXQ_t ;
typedef  TYPE_13__ IOCB_t ;

/* Variables and functions */
 scalar_t__ ADD_STATUS_INVALID_REQUEST ; 
 scalar_t__ ADD_STATUS_OPERATION_ALREADY_ACTIVE ; 
 scalar_t__ ELS_CMD_ACC ; 
 scalar_t__ ELS_CMD_LS_RJT ; 
 int IOCB_ERROR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 int /*<<< orphan*/  LSEXP_CMD_IN_PROGRESS ; 
 int /*<<< orphan*/  LSRJT_UNABLE_TPC ; 
 scalar_t__ MBX_SUCCESS ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lpfc_lcb_context*) ; 
 void* lpfc_cmpl_els_rsp ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_max_els_tries ; 
 int /*<<< orphan*/  lpfc_mbox_hdr_add_status ; 
 int /*<<< orphan*/  lpfc_mbox_hdr_status ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_lcb_res_frame*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lpfc_els_lcb_rsp(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb;
	IOCB_t *icmd;
	uint8_t *pcmd;
	struct lpfc_iocbq *elsiocb;
	struct lpfc_nodelist *ndlp;
	struct ls_rjt *stat;
	union lpfc_sli4_cfg_shdr *shdr;
	struct lpfc_lcb_context *lcb_context;
	struct fc_lcb_res_frame *lcb_res;
	uint32_t cmdsize, shdr_status, shdr_add_status;
	int rc;

	mb = &pmb->u.mb;
	lcb_context = (struct lpfc_lcb_context *)pmb->ctx_ndlp;
	ndlp = lcb_context->ndlp;
	pmb->ctx_ndlp = NULL;
	pmb->ctx_buf = NULL;

	shdr = (union lpfc_sli4_cfg_shdr *)
			&pmb->u.mqe.un.beacon_config.header.cfg_shdr;
	shdr_status = bf_get(lpfc_mbox_hdr_status, &shdr->response);
	shdr_add_status = bf_get(lpfc_mbox_hdr_add_status, &shdr->response);

	lpfc_printf_log(phba, KERN_INFO, LOG_MBOX,
				"0194 SET_BEACON_CONFIG mailbox "
				"completed with status x%x add_status x%x,"
				" mbx status x%x\n",
				shdr_status, shdr_add_status, mb->mbxStatus);

	if ((mb->mbxStatus != MBX_SUCCESS) || shdr_status ||
	    (shdr_add_status == ADD_STATUS_OPERATION_ALREADY_ACTIVE) ||
	    (shdr_add_status == ADD_STATUS_INVALID_REQUEST)) {
		mempool_free(pmb, phba->mbox_mem_pool);
		goto error;
	}

	mempool_free(pmb, phba->mbox_mem_pool);
	cmdsize = sizeof(struct fc_lcb_res_frame);
	elsiocb = lpfc_prep_els_iocb(phba->pport, 0, cmdsize,
			lpfc_max_els_tries, ndlp,
			ndlp->nlp_DID, ELS_CMD_ACC);

	/* Decrement the ndlp reference count from previous mbox command */
	lpfc_nlp_put(ndlp);

	if (!elsiocb)
		goto free_lcb_context;

	lcb_res = (struct fc_lcb_res_frame *)
		(((struct lpfc_dmabuf *)elsiocb->context2)->virt);

	memset(lcb_res, 0, sizeof(struct fc_lcb_res_frame));
	icmd = &elsiocb->iocb;
	icmd->ulpContext = lcb_context->rx_id;
	icmd->unsli3.rcvsli3.ox_id = lcb_context->ox_id;

	pcmd = (uint8_t *)(((struct lpfc_dmabuf *)elsiocb->context2)->virt);
	*((uint32_t *)(pcmd)) = ELS_CMD_ACC;
	lcb_res->lcb_sub_command = lcb_context->sub_command;
	lcb_res->lcb_type = lcb_context->type;
	lcb_res->capability = lcb_context->capability;
	lcb_res->lcb_frequency = lcb_context->frequency;
	lcb_res->lcb_duration = lcb_context->duration;
	elsiocb->iocb_cmpl = lpfc_cmpl_els_rsp;
	phba->fc_stat.elsXmitACC++;
	rc = lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0);
	if (rc == IOCB_ERROR)
		lpfc_els_free_iocb(phba, elsiocb);

	kfree(lcb_context);
	return;

error:
	cmdsize = sizeof(struct fc_lcb_res_frame);
	elsiocb = lpfc_prep_els_iocb(phba->pport, 0, cmdsize,
			lpfc_max_els_tries, ndlp,
			ndlp->nlp_DID, ELS_CMD_LS_RJT);
	lpfc_nlp_put(ndlp);
	if (!elsiocb)
		goto free_lcb_context;

	icmd = &elsiocb->iocb;
	icmd->ulpContext = lcb_context->rx_id;
	icmd->unsli3.rcvsli3.ox_id = lcb_context->ox_id;
	pcmd = (uint8_t *)(((struct lpfc_dmabuf *)elsiocb->context2)->virt);

	*((uint32_t *)(pcmd)) = ELS_CMD_LS_RJT;
	stat = (struct ls_rjt *)(pcmd + sizeof(uint32_t));
	stat->un.b.lsRjtRsnCode = LSRJT_UNABLE_TPC;

	if (shdr_add_status == ADD_STATUS_OPERATION_ALREADY_ACTIVE)
		stat->un.b.lsRjtRsnCodeExp = LSEXP_CMD_IN_PROGRESS;

	elsiocb->iocb_cmpl = lpfc_cmpl_els_rsp;
	phba->fc_stat.elsXmitLSRJT++;
	rc = lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0);
	if (rc == IOCB_ERROR)
		lpfc_els_free_iocb(phba, elsiocb);
free_lcb_context:
	kfree(lcb_context);
}