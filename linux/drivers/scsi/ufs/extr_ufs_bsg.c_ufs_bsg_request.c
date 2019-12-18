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
typedef  int /*<<< orphan*/  uint8_t ;
struct uic_command {int dummy; } ;
struct ufs_hba {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int opcode; } ;
struct TYPE_9__ {struct uic_command uc; TYPE_2__ qr; } ;
struct ufs_bsg_request {int msgcode; TYPE_4__ upiu_req; } ;
struct TYPE_10__ {struct uic_command uc; } ;
struct ufs_bsg_reply {int result; scalar_t__ reply_payload_rcv_len; TYPE_5__ upiu_rsp; } ;
struct TYPE_8__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {unsigned int request_len; unsigned int reply_len; TYPE_3__ request_payload; TYPE_1__* dev; struct ufs_bsg_reply* reply; struct ufs_bsg_request* request; } ;
typedef  enum query_opcode { ____Placeholder_query_opcode } query_opcode ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  UIC_CMD_SIZE ; 
 int UPIU_QUERY_OPCODE_NOP ; 
 int UPIU_QUERY_OPCODE_READ_DESC ; 
#define  UPIU_TRANSACTION_NOP_OUT 131 
#define  UPIU_TRANSACTION_QUERY_REQ 130 
#define  UPIU_TRANSACTION_TASK_REQ 129 
#define  UPIU_TRANSACTION_UIC_CMD 128 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_to_shost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct uic_command*,struct uic_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct ufs_hba* shost_priv (int /*<<< orphan*/ ) ; 
 int ufs_bsg_alloc_desc_buffer (struct ufs_hba*,struct bsg_job*,int /*<<< orphan*/ **,int*,int) ; 
 int ufs_bsg_verify_query_size (struct ufs_hba*,unsigned int,unsigned int) ; 
 int ufshcd_exec_raw_upiu_cmd (struct ufs_hba*,TYPE_4__*,TYPE_5__*,int,int /*<<< orphan*/ *,int*,int) ; 
 int ufshcd_send_uic_cmd (struct ufs_hba*,struct uic_command*) ; 

__attribute__((used)) static int ufs_bsg_request(struct bsg_job *job)
{
	struct ufs_bsg_request *bsg_request = job->request;
	struct ufs_bsg_reply *bsg_reply = job->reply;
	struct ufs_hba *hba = shost_priv(dev_to_shost(job->dev->parent));
	unsigned int req_len = job->request_len;
	unsigned int reply_len = job->reply_len;
	struct uic_command uc = {};
	int msgcode;
	uint8_t *desc_buff = NULL;
	int desc_len = 0;
	enum query_opcode desc_op = UPIU_QUERY_OPCODE_NOP;
	int ret;

	ret = ufs_bsg_verify_query_size(hba, req_len, reply_len);
	if (ret)
		goto out;

	bsg_reply->reply_payload_rcv_len = 0;

	pm_runtime_get_sync(hba->dev);

	msgcode = bsg_request->msgcode;
	switch (msgcode) {
	case UPIU_TRANSACTION_QUERY_REQ:
		desc_op = bsg_request->upiu_req.qr.opcode;
		ret = ufs_bsg_alloc_desc_buffer(hba, job, &desc_buff,
						&desc_len, desc_op);
		if (ret)
			goto out;

		/* fall through */
	case UPIU_TRANSACTION_NOP_OUT:
	case UPIU_TRANSACTION_TASK_REQ:
		ret = ufshcd_exec_raw_upiu_cmd(hba, &bsg_request->upiu_req,
					       &bsg_reply->upiu_rsp, msgcode,
					       desc_buff, &desc_len, desc_op);
		if (ret)
			dev_err(hba->dev,
				"exe raw upiu: error code %d\n", ret);

		break;
	case UPIU_TRANSACTION_UIC_CMD:
		memcpy(&uc, &bsg_request->upiu_req.uc, UIC_CMD_SIZE);
		ret = ufshcd_send_uic_cmd(hba, &uc);
		if (ret)
			dev_err(hba->dev,
				"send uic cmd: error code %d\n", ret);

		memcpy(&bsg_reply->upiu_rsp.uc, &uc, UIC_CMD_SIZE);

		break;
	default:
		ret = -ENOTSUPP;
		dev_err(hba->dev, "unsupported msgcode 0x%x\n", msgcode);

		break;
	}

	pm_runtime_put_sync(hba->dev);

	if (!desc_buff)
		goto out;

	if (desc_op == UPIU_QUERY_OPCODE_READ_DESC && desc_len)
		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(job->request_payload.sg_list,
					    job->request_payload.sg_cnt,
					    desc_buff, desc_len);

	kfree(desc_buff);

out:
	bsg_reply->result = ret;
	job->reply_len = sizeof(struct ufs_bsg_reply);
	/* complete the job here only if no error */
	if (ret == 0)
		bsg_job_done(job, ret, bsg_reply->reply_payload_rcv_len);

	return ret;
}