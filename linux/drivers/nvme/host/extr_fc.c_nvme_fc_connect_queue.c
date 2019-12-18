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
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct nvmefc_ls_req {int rqstlen; int rsplen; int /*<<< orphan*/  timeout; struct fcnvme_ls_cr_conn_acc* rspaddr; struct fcnvme_ls_cr_conn_rqst* rqstaddr; void* private; } ;
struct nvmefc_ls_req_op {struct nvme_fc_queue* queue; struct nvmefc_ls_req ls_req; } ;
struct nvme_fc_queue {scalar_t__ qnum; int /*<<< orphan*/  flags; int /*<<< orphan*/  connection_id; } ;
struct nvme_fc_ctrl {int /*<<< orphan*/  dev; int /*<<< orphan*/  rport; int /*<<< orphan*/  association_id; TYPE_2__* lport; } ;
struct fcnvme_lsdesc_rqst {int dummy; } ;
struct fcnvme_lsdesc_cr_conn_cmd {int dummy; } ;
struct fcnvme_lsdesc_conn_id {int dummy; } ;
struct fcnvme_lsdesc_assoc_id {int dummy; } ;
struct TYPE_16__ {void* sqsize; void* qid; void* ersp_ratio; scalar_t__ desc_len; scalar_t__ desc_tag; } ;
struct TYPE_15__ {int /*<<< orphan*/  association_id; scalar_t__ desc_len; scalar_t__ desc_tag; } ;
struct TYPE_14__ {scalar_t__ ls_cmd; } ;
struct fcnvme_ls_cr_conn_rqst {TYPE_5__ connect_cmd; TYPE_4__ associd; scalar_t__ desc_list_len; TYPE_3__ w0; } ;
struct TYPE_11__ {scalar_t__ desc_tag; scalar_t__ desc_len; int /*<<< orphan*/  connection_id; } ;
struct TYPE_18__ {scalar_t__ ls_cmd; } ;
struct TYPE_19__ {scalar_t__ desc_tag; scalar_t__ desc_len; TYPE_7__ w0; } ;
struct TYPE_17__ {scalar_t__ ls_cmd; } ;
struct TYPE_20__ {scalar_t__ desc_list_len; TYPE_8__ rqst; TYPE_6__ w0; } ;
struct fcnvme_ls_cr_conn_acc {TYPE_10__ connectid; TYPE_9__ hdr; } ;
struct TYPE_13__ {TYPE_1__* ops; } ;
struct TYPE_12__ {int lsrqst_priv_sz; } ;

/* Variables and functions */
 int EBADF ; 
 int ENOMEM ; 
 int FCNVME_LSDESC_ASSOC_ID ; 
 int FCNVME_LSDESC_CONN_ID ; 
 int FCNVME_LSDESC_CREATE_CONN_CMD ; 
 int FCNVME_LSDESC_RQST ; 
 scalar_t__ FCNVME_LS_ACC ; 
 scalar_t__ FCNVME_LS_CREATE_CONNECTION ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_FC_CONNECT_TIMEOUT_SEC ; 
 int /*<<< orphan*/  NVME_FC_Q_CONNECTED ; 
 int VERR_CONN_ID ; 
 int VERR_CONN_ID_LEN ; 
 int VERR_CR_CONN ; 
 int VERR_CR_CONN_ACC_LEN ; 
 int VERR_LSACC ; 
 int VERR_LSDESC_RQST ; 
 int VERR_LSDESC_RQST_LEN ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (scalar_t__) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 scalar_t__ fcnvme_lsdesc_len (int) ; 
 int /*<<< orphan*/  kfree (struct nvmefc_ls_req_op*) ; 
 struct nvmefc_ls_req_op* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvme_fc_send_ls_req (int /*<<< orphan*/ ,struct nvmefc_ls_req_op*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* validation_errors ; 

__attribute__((used)) static int
nvme_fc_connect_queue(struct nvme_fc_ctrl *ctrl, struct nvme_fc_queue *queue,
			u16 qsize, u16 ersp_ratio)
{
	struct nvmefc_ls_req_op *lsop;
	struct nvmefc_ls_req *lsreq;
	struct fcnvme_ls_cr_conn_rqst *conn_rqst;
	struct fcnvme_ls_cr_conn_acc *conn_acc;
	int ret, fcret = 0;

	lsop = kzalloc((sizeof(*lsop) +
			 ctrl->lport->ops->lsrqst_priv_sz +
			 sizeof(*conn_rqst) + sizeof(*conn_acc)), GFP_KERNEL);
	if (!lsop) {
		ret = -ENOMEM;
		goto out_no_memory;
	}
	lsreq = &lsop->ls_req;

	lsreq->private = (void *)&lsop[1];
	conn_rqst = (struct fcnvme_ls_cr_conn_rqst *)
			(lsreq->private + ctrl->lport->ops->lsrqst_priv_sz);
	conn_acc = (struct fcnvme_ls_cr_conn_acc *)&conn_rqst[1];

	conn_rqst->w0.ls_cmd = FCNVME_LS_CREATE_CONNECTION;
	conn_rqst->desc_list_len = cpu_to_be32(
				sizeof(struct fcnvme_lsdesc_assoc_id) +
				sizeof(struct fcnvme_lsdesc_cr_conn_cmd));

	conn_rqst->associd.desc_tag = cpu_to_be32(FCNVME_LSDESC_ASSOC_ID);
	conn_rqst->associd.desc_len =
			fcnvme_lsdesc_len(
				sizeof(struct fcnvme_lsdesc_assoc_id));
	conn_rqst->associd.association_id = cpu_to_be64(ctrl->association_id);
	conn_rqst->connect_cmd.desc_tag =
			cpu_to_be32(FCNVME_LSDESC_CREATE_CONN_CMD);
	conn_rqst->connect_cmd.desc_len =
			fcnvme_lsdesc_len(
				sizeof(struct fcnvme_lsdesc_cr_conn_cmd));
	conn_rqst->connect_cmd.ersp_ratio = cpu_to_be16(ersp_ratio);
	conn_rqst->connect_cmd.qid  = cpu_to_be16(queue->qnum);
	conn_rqst->connect_cmd.sqsize = cpu_to_be16(qsize - 1);

	lsop->queue = queue;
	lsreq->rqstaddr = conn_rqst;
	lsreq->rqstlen = sizeof(*conn_rqst);
	lsreq->rspaddr = conn_acc;
	lsreq->rsplen = sizeof(*conn_acc);
	lsreq->timeout = NVME_FC_CONNECT_TIMEOUT_SEC;

	ret = nvme_fc_send_ls_req(ctrl->rport, lsop);
	if (ret)
		goto out_free_buffer;

	/* process connect LS completion */

	/* validate the ACC response */
	if (conn_acc->hdr.w0.ls_cmd != FCNVME_LS_ACC)
		fcret = VERR_LSACC;
	else if (conn_acc->hdr.desc_list_len !=
			fcnvme_lsdesc_len(sizeof(struct fcnvme_ls_cr_conn_acc)))
		fcret = VERR_CR_CONN_ACC_LEN;
	else if (conn_acc->hdr.rqst.desc_tag != cpu_to_be32(FCNVME_LSDESC_RQST))
		fcret = VERR_LSDESC_RQST;
	else if (conn_acc->hdr.rqst.desc_len !=
			fcnvme_lsdesc_len(sizeof(struct fcnvme_lsdesc_rqst)))
		fcret = VERR_LSDESC_RQST_LEN;
	else if (conn_acc->hdr.rqst.w0.ls_cmd != FCNVME_LS_CREATE_CONNECTION)
		fcret = VERR_CR_CONN;
	else if (conn_acc->connectid.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_CONN_ID))
		fcret = VERR_CONN_ID;
	else if (conn_acc->connectid.desc_len !=
			fcnvme_lsdesc_len(sizeof(struct fcnvme_lsdesc_conn_id)))
		fcret = VERR_CONN_ID_LEN;

	if (fcret) {
		ret = -EBADF;
		dev_err(ctrl->dev,
			"q %d connect failed: %s\n",
			queue->qnum, validation_errors[fcret]);
	} else {
		queue->connection_id =
			be64_to_cpu(conn_acc->connectid.connection_id);
		set_bit(NVME_FC_Q_CONNECTED, &queue->flags);
	}

out_free_buffer:
	kfree(lsop);
out_no_memory:
	if (ret)
		dev_err(ctrl->dev,
			"queue %d connect command failed (%d).\n",
			queue->qnum, ret);
	return ret;
}