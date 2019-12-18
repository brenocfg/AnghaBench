#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvmet_fc_tgtport {int /*<<< orphan*/  dev; } ;
struct nvmet_fc_tgt_queue {scalar_t__ sqhd; int /*<<< orphan*/  connected; scalar_t__ ersp_ratio; } ;
struct nvmet_fc_ls_iod {scalar_t__ rqstdatalen; int /*<<< orphan*/  assoc; TYPE_3__* lsreq; scalar_t__ rspbuf; scalar_t__ rqstbuf; } ;
struct fcnvme_lsdesc_conn_id {int dummy; } ;
struct fcnvme_lsdesc_assoc_id {int dummy; } ;
struct TYPE_7__ {scalar_t__ desc_tag; int /*<<< orphan*/  ersp_ratio; int /*<<< orphan*/  sqsize; int /*<<< orphan*/  desc_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  ls_cmd; } ;
struct fcnvme_ls_cr_assoc_rqst {TYPE_2__ assoc_cmd; TYPE_1__ w0; int /*<<< orphan*/  desc_list_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  association_id; void* desc_len; scalar_t__ desc_tag; } ;
struct TYPE_9__ {int /*<<< orphan*/  connection_id; void* desc_len; scalar_t__ desc_tag; } ;
struct fcnvme_ls_cr_assoc_acc {TYPE_5__ associd; TYPE_4__ connectid; } ;
struct TYPE_8__ {int rsplen; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCNVME_LSDESC_ASSOC_ID ; 
 int /*<<< orphan*/  FCNVME_LSDESC_CONN_ID ; 
 scalar_t__ FCNVME_LSDESC_CRA_CMD_DESC_MIN_DESCLEN ; 
 scalar_t__ FCNVME_LSDESC_CRA_RQST_MINLEN ; 
 scalar_t__ FCNVME_LSDESC_CRA_RQST_MIN_LISTLEN ; 
 int /*<<< orphan*/  FCNVME_LSDESC_CREATE_ASSOC_CMD ; 
 int /*<<< orphan*/  FCNVME_LS_ACC ; 
 int /*<<< orphan*/  FCNVME_LS_CREATE_ASSOCIATION ; 
 int /*<<< orphan*/  FCNVME_RJT_EXP_NONE ; 
 int /*<<< orphan*/  FCNVME_RJT_RC_LOGIC ; 
 int /*<<< orphan*/  NVME_FC_MAX_LS_BUFFER_SIZE ; 
 int VERR_ASSOC_ALLOC_FAIL ; 
 int VERR_CR_ASSOC_CMD ; 
 int VERR_CR_ASSOC_CMD_LEN ; 
 int VERR_CR_ASSOC_LEN ; 
 int VERR_CR_ASSOC_RQST_LEN ; 
 int VERR_ERSP_RATIO ; 
 int VERR_QUEUE_ALLOC_FAIL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* fcnvme_lsdesc_len (int) ; 
 int /*<<< orphan*/  memset (struct fcnvme_ls_cr_assoc_acc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvmet_fc_alloc_target_assoc (struct nvmet_fc_tgtport*) ; 
 struct nvmet_fc_tgt_queue* nvmet_fc_alloc_target_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int nvmet_fc_format_rjt (struct fcnvme_ls_cr_assoc_acc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_fc_format_rsp_hdr (struct fcnvme_ls_cr_assoc_acc*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_fc_makeconnid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * validation_errors ; 

__attribute__((used)) static void
nvmet_fc_ls_create_association(struct nvmet_fc_tgtport *tgtport,
			struct nvmet_fc_ls_iod *iod)
{
	struct fcnvme_ls_cr_assoc_rqst *rqst =
				(struct fcnvme_ls_cr_assoc_rqst *)iod->rqstbuf;
	struct fcnvme_ls_cr_assoc_acc *acc =
				(struct fcnvme_ls_cr_assoc_acc *)iod->rspbuf;
	struct nvmet_fc_tgt_queue *queue;
	int ret = 0;

	memset(acc, 0, sizeof(*acc));

	/*
	 * FC-NVME spec changes. There are initiators sending different
	 * lengths as padding sizes for Create Association Cmd descriptor
	 * was incorrect.
	 * Accept anything of "minimum" length. Assume format per 1.15
	 * spec (with HOSTID reduced to 16 bytes), ignore how long the
	 * trailing pad length is.
	 */
	if (iod->rqstdatalen < FCNVME_LSDESC_CRA_RQST_MINLEN)
		ret = VERR_CR_ASSOC_LEN;
	else if (be32_to_cpu(rqst->desc_list_len) <
			FCNVME_LSDESC_CRA_RQST_MIN_LISTLEN)
		ret = VERR_CR_ASSOC_RQST_LEN;
	else if (rqst->assoc_cmd.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_CREATE_ASSOC_CMD))
		ret = VERR_CR_ASSOC_CMD;
	else if (be32_to_cpu(rqst->assoc_cmd.desc_len) <
			FCNVME_LSDESC_CRA_CMD_DESC_MIN_DESCLEN)
		ret = VERR_CR_ASSOC_CMD_LEN;
	else if (!rqst->assoc_cmd.ersp_ratio ||
		 (be16_to_cpu(rqst->assoc_cmd.ersp_ratio) >=
				be16_to_cpu(rqst->assoc_cmd.sqsize)))
		ret = VERR_ERSP_RATIO;

	else {
		/* new association w/ admin queue */
		iod->assoc = nvmet_fc_alloc_target_assoc(tgtport);
		if (!iod->assoc)
			ret = VERR_ASSOC_ALLOC_FAIL;
		else {
			queue = nvmet_fc_alloc_target_queue(iod->assoc, 0,
					be16_to_cpu(rqst->assoc_cmd.sqsize));
			if (!queue)
				ret = VERR_QUEUE_ALLOC_FAIL;
		}
	}

	if (ret) {
		dev_err(tgtport->dev,
			"Create Association LS failed: %s\n",
			validation_errors[ret]);
		iod->lsreq->rsplen = nvmet_fc_format_rjt(acc,
				NVME_FC_MAX_LS_BUFFER_SIZE, rqst->w0.ls_cmd,
				FCNVME_RJT_RC_LOGIC,
				FCNVME_RJT_EXP_NONE, 0);
		return;
	}

	queue->ersp_ratio = be16_to_cpu(rqst->assoc_cmd.ersp_ratio);
	atomic_set(&queue->connected, 1);
	queue->sqhd = 0;	/* best place to init value */

	/* format a response */

	iod->lsreq->rsplen = sizeof(*acc);

	nvmet_fc_format_rsp_hdr(acc, FCNVME_LS_ACC,
			fcnvme_lsdesc_len(
				sizeof(struct fcnvme_ls_cr_assoc_acc)),
			FCNVME_LS_CREATE_ASSOCIATION);
	acc->associd.desc_tag = cpu_to_be32(FCNVME_LSDESC_ASSOC_ID);
	acc->associd.desc_len =
			fcnvme_lsdesc_len(
				sizeof(struct fcnvme_lsdesc_assoc_id));
	acc->associd.association_id =
			cpu_to_be64(nvmet_fc_makeconnid(iod->assoc, 0));
	acc->connectid.desc_tag = cpu_to_be32(FCNVME_LSDESC_CONN_ID);
	acc->connectid.desc_len =
			fcnvme_lsdesc_len(
				sizeof(struct fcnvme_lsdesc_conn_id));
	acc->connectid.connection_id = acc->associd.association_id;
}