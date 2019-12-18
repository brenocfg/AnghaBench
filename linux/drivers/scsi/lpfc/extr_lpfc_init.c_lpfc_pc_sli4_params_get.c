#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_pc_sli4_params {scalar_t__ sge_supp_len; void* sgl_pp_align; void* sgl_pages_max; void* hdr_pp_align; void* hdr_size; void* hdr_pages_max; void* rqe_size; void* rq_pages_max; void* wqe_size; void* wq_pages_max; void* mq_elem_cnt; void* mqe_size; void* mq_pages_max; void* cqe_size; void* cq_pages_max; void* eqe_size; void* eq_pages_max; void* loopbk_scope; void* rq_db_window; void* if_page_sz; int /*<<< orphan*/  proto_types; void* featurelevel_2; void* featurelevel_1; void* sli_family; void* sli_rev; void* if_type; } ;
struct TYPE_11__ {scalar_t__ sge_supp_len; int /*<<< orphan*/  word3; } ;
struct TYPE_14__ {TYPE_10__ sli4_params; } ;
struct lpfc_mqe {TYPE_3__ un; } ;
struct TYPE_13__ {struct lpfc_pc_sli4_params pc_sli4_params; int /*<<< orphan*/  intr_enable; } ;
struct lpfc_hba {TYPE_2__ sli4_hba; } ;
struct TYPE_12__ {struct lpfc_mqe mqe; } ;
struct TYPE_15__ {TYPE_1__ u; } ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;

/* Variables and functions */
 scalar_t__ LPFC_MAX_SGE_SIZE ; 
 int /*<<< orphan*/  MBX_POLL ; 
 void* bf_get (int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  cq_pages ; 
 int /*<<< orphan*/  cqe_size ; 
 int /*<<< orphan*/  eq_pages ; 
 int /*<<< orphan*/  eqe_size ; 
 int /*<<< orphan*/  featurelevel_1 ; 
 int /*<<< orphan*/  featurelevel_2 ; 
 int /*<<< orphan*/  hdr_pages ; 
 int /*<<< orphan*/  hdr_pp_align ; 
 int /*<<< orphan*/  hdr_size ; 
 int /*<<< orphan*/  if_page_sz ; 
 int /*<<< orphan*/  if_type ; 
 int /*<<< orphan*/  loopbk_scope ; 
 int /*<<< orphan*/  lpfc_mbox_tmo_val (struct lpfc_hba*,TYPE_4__*) ; 
 int /*<<< orphan*/  lpfc_pc_sli4_params (TYPE_4__*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_mbox_wait (struct lpfc_hba*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mq_elem_cnt ; 
 int /*<<< orphan*/  mq_pages ; 
 int /*<<< orphan*/  mqe_size ; 
 int /*<<< orphan*/  rq_db_window ; 
 int /*<<< orphan*/  rq_pages ; 
 int /*<<< orphan*/  rqe_size ; 
 int /*<<< orphan*/  sgl_pages ; 
 int /*<<< orphan*/  sgl_pp_align ; 
 int /*<<< orphan*/  sli_family ; 
 int /*<<< orphan*/  sli_rev ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wq_pages ; 
 int /*<<< orphan*/  wqe_size ; 

int
lpfc_pc_sli4_params_get(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	int rc;
	struct lpfc_mqe *mqe;
	struct lpfc_pc_sli4_params *sli4_params;
	uint32_t mbox_tmo;

	rc = 0;
	mqe = &mboxq->u.mqe;

	/* Read the port's SLI4 Parameters port capabilities */
	lpfc_pc_sli4_params(mboxq);
	if (!phba->sli4_hba.intr_enable)
		rc = lpfc_sli_issue_mbox(phba, mboxq, MBX_POLL);
	else {
		mbox_tmo = lpfc_mbox_tmo_val(phba, mboxq);
		rc = lpfc_sli_issue_mbox_wait(phba, mboxq, mbox_tmo);
	}

	if (unlikely(rc))
		return 1;

	sli4_params = &phba->sli4_hba.pc_sli4_params;
	sli4_params->if_type = bf_get(if_type, &mqe->un.sli4_params);
	sli4_params->sli_rev = bf_get(sli_rev, &mqe->un.sli4_params);
	sli4_params->sli_family = bf_get(sli_family, &mqe->un.sli4_params);
	sli4_params->featurelevel_1 = bf_get(featurelevel_1,
					     &mqe->un.sli4_params);
	sli4_params->featurelevel_2 = bf_get(featurelevel_2,
					     &mqe->un.sli4_params);
	sli4_params->proto_types = mqe->un.sli4_params.word3;
	sli4_params->sge_supp_len = mqe->un.sli4_params.sge_supp_len;
	sli4_params->if_page_sz = bf_get(if_page_sz, &mqe->un.sli4_params);
	sli4_params->rq_db_window = bf_get(rq_db_window, &mqe->un.sli4_params);
	sli4_params->loopbk_scope = bf_get(loopbk_scope, &mqe->un.sli4_params);
	sli4_params->eq_pages_max = bf_get(eq_pages, &mqe->un.sli4_params);
	sli4_params->eqe_size = bf_get(eqe_size, &mqe->un.sli4_params);
	sli4_params->cq_pages_max = bf_get(cq_pages, &mqe->un.sli4_params);
	sli4_params->cqe_size = bf_get(cqe_size, &mqe->un.sli4_params);
	sli4_params->mq_pages_max = bf_get(mq_pages, &mqe->un.sli4_params);
	sli4_params->mqe_size = bf_get(mqe_size, &mqe->un.sli4_params);
	sli4_params->mq_elem_cnt = bf_get(mq_elem_cnt, &mqe->un.sli4_params);
	sli4_params->wq_pages_max = bf_get(wq_pages, &mqe->un.sli4_params);
	sli4_params->wqe_size = bf_get(wqe_size, &mqe->un.sli4_params);
	sli4_params->rq_pages_max = bf_get(rq_pages, &mqe->un.sli4_params);
	sli4_params->rqe_size = bf_get(rqe_size, &mqe->un.sli4_params);
	sli4_params->hdr_pages_max = bf_get(hdr_pages, &mqe->un.sli4_params);
	sli4_params->hdr_size = bf_get(hdr_size, &mqe->un.sli4_params);
	sli4_params->hdr_pp_align = bf_get(hdr_pp_align, &mqe->un.sli4_params);
	sli4_params->sgl_pages_max = bf_get(sgl_pages, &mqe->un.sli4_params);
	sli4_params->sgl_pp_align = bf_get(sgl_pp_align, &mqe->un.sli4_params);

	/* Make sure that sge_supp_len can be handled by the driver */
	if (sli4_params->sge_supp_len > LPFC_MAX_SGE_SIZE)
		sli4_params->sge_supp_len = LPFC_MAX_SGE_SIZE;

	return rc;
}