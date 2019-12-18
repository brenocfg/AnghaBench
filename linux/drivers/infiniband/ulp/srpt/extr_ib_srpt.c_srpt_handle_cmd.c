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
typedef  int /*<<< orphan*/  u64 ;
struct se_cmd {int /*<<< orphan*/  sam_task_attr; int /*<<< orphan*/  tag; } ;
struct srpt_send_ioctx {int /*<<< orphan*/ * sense_data; struct se_cmd cmd; } ;
struct TYPE_2__ {int offset; struct srp_cmd* buf; } ;
struct srpt_recv_ioctx {TYPE_1__ ioctx; } ;
struct srpt_rdma_ch {int /*<<< orphan*/  sess; int /*<<< orphan*/  imm_data_offset; } ;
struct srp_cmd {int task_attr; int /*<<< orphan*/  tag; int /*<<< orphan*/  lun; int /*<<< orphan*/  cdb; } ;
struct scatterlist {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
#define  SRP_CMD_ACA 131 
#define  SRP_CMD_HEAD_OF_Q 130 
#define  SRP_CMD_ORDERED_Q 129 
#define  SRP_CMD_SIMPLE_Q 128 
 int /*<<< orphan*/  TARGET_SCF_ACK_KREF ; 
 int /*<<< orphan*/  TCM_ACA_TAG ; 
 int /*<<< orphan*/  TCM_HEAD_TAG ; 
 int /*<<< orphan*/  TCM_ORDERED_TAG ; 
 int /*<<< orphan*/  TCM_SIMPLE_TAG ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsilun_to_int (int /*<<< orphan*/ *) ; 
 int srpt_get_desc_tbl (struct srpt_recv_ioctx*,struct srpt_send_ioctx*,struct srp_cmd*,int*,struct scatterlist**,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_send_busy (struct se_cmd*) ; 
 int target_submit_cmd_map_sgls (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srpt_handle_cmd(struct srpt_rdma_ch *ch,
			    struct srpt_recv_ioctx *recv_ioctx,
			    struct srpt_send_ioctx *send_ioctx)
{
	struct se_cmd *cmd;
	struct srp_cmd *srp_cmd;
	struct scatterlist *sg = NULL;
	unsigned sg_cnt = 0;
	u64 data_len;
	enum dma_data_direction dir;
	int rc;

	BUG_ON(!send_ioctx);

	srp_cmd = recv_ioctx->ioctx.buf + recv_ioctx->ioctx.offset;
	cmd = &send_ioctx->cmd;
	cmd->tag = srp_cmd->tag;

	switch (srp_cmd->task_attr) {
	case SRP_CMD_SIMPLE_Q:
		cmd->sam_task_attr = TCM_SIMPLE_TAG;
		break;
	case SRP_CMD_ORDERED_Q:
	default:
		cmd->sam_task_attr = TCM_ORDERED_TAG;
		break;
	case SRP_CMD_HEAD_OF_Q:
		cmd->sam_task_attr = TCM_HEAD_TAG;
		break;
	case SRP_CMD_ACA:
		cmd->sam_task_attr = TCM_ACA_TAG;
		break;
	}

	rc = srpt_get_desc_tbl(recv_ioctx, send_ioctx, srp_cmd, &dir,
			       &sg, &sg_cnt, &data_len, ch->imm_data_offset);
	if (rc) {
		if (rc != -EAGAIN) {
			pr_err("0x%llx: parsing SRP descriptor table failed.\n",
			       srp_cmd->tag);
		}
		goto busy;
	}

	rc = target_submit_cmd_map_sgls(cmd, ch->sess, srp_cmd->cdb,
			       &send_ioctx->sense_data[0],
			       scsilun_to_int(&srp_cmd->lun), data_len,
			       TCM_SIMPLE_TAG, dir, TARGET_SCF_ACK_KREF,
			       sg, sg_cnt, NULL, 0, NULL, 0);
	if (rc != 0) {
		pr_debug("target_submit_cmd() returned %d for tag %#llx\n", rc,
			 srp_cmd->tag);
		goto busy;
	}
	return;

busy:
	target_send_busy(cmd);
}