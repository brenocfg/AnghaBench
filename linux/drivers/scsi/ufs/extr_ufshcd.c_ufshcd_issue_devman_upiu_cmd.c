#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dword_2; int /*<<< orphan*/  dword_0; } ;
struct utp_upiu_req {TYPE_2__ header; } ;
typedef  struct utp_upiu_req u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct utp_upiu_rsp {int dummy; } ;
struct ufshcd_lrb {int task_tag; int intr_cmd; struct utp_upiu_req* ucd_rsp_ptr; struct utp_upiu_req* ucd_req_ptr; int /*<<< orphan*/  command_type; scalar_t__ lun; int /*<<< orphan*/ * sense_buffer; scalar_t__ sense_bufflen; int /*<<< orphan*/ * cmd; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  tag_wq; struct completion* complete; } ;
struct ufs_hba {int ufs_version; int /*<<< orphan*/  clk_scaling_lock; TYPE_3__ dev_cmd; int /*<<< orphan*/  dev; TYPE_1__* host; struct ufshcd_lrb* lrb; } ;
struct completion {int dummy; } ;
typedef  enum query_opcode { ____Placeholder_query_opcode } query_opcode ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int EINVAL ; 
 int MASK_QUERY_DATA_SEG_LEN ; 
 int /*<<< orphan*/  QUERY_REQ_TIMEOUT ; 
#define  UFSHCI_VERSION_10 129 
#define  UFSHCI_VERSION_11 128 
 int UPIU_QUERY_OPCODE_READ_DESC ; 
 int UPIU_QUERY_OPCODE_WRITE_DESC ; 
 int /*<<< orphan*/  UTP_CMD_TYPE_DEV_MANAGE ; 
 int /*<<< orphan*/  UTP_CMD_TYPE_UFS_STORAGE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ *) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  memcpy (struct utp_upiu_req*,struct utp_upiu_req*,int) ; 
 int /*<<< orphan*/  memset (struct utp_upiu_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ufshcd_get_dev_cmd_tag (struct ufs_hba*,int*) ; 
 int /*<<< orphan*/  ufshcd_prepare_req_desc_hdr (struct ufshcd_lrb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_put_dev_cmd_tag (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_send_command (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_wait_for_dev_cmd (struct ufs_hba*,struct ufshcd_lrb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ufshcd_issue_devman_upiu_cmd(struct ufs_hba *hba,
					struct utp_upiu_req *req_upiu,
					struct utp_upiu_req *rsp_upiu,
					u8 *desc_buff, int *buff_len,
					int cmd_type,
					enum query_opcode desc_op)
{
	struct ufshcd_lrb *lrbp;
	int err = 0;
	int tag;
	struct completion wait;
	unsigned long flags;
	u32 upiu_flags;

	down_read(&hba->clk_scaling_lock);

	wait_event(hba->dev_cmd.tag_wq, ufshcd_get_dev_cmd_tag(hba, &tag));

	init_completion(&wait);
	lrbp = &hba->lrb[tag];
	WARN_ON(lrbp->cmd);

	lrbp->cmd = NULL;
	lrbp->sense_bufflen = 0;
	lrbp->sense_buffer = NULL;
	lrbp->task_tag = tag;
	lrbp->lun = 0;
	lrbp->intr_cmd = true;
	hba->dev_cmd.type = cmd_type;

	switch (hba->ufs_version) {
	case UFSHCI_VERSION_10:
	case UFSHCI_VERSION_11:
		lrbp->command_type = UTP_CMD_TYPE_DEV_MANAGE;
		break;
	default:
		lrbp->command_type = UTP_CMD_TYPE_UFS_STORAGE;
		break;
	}

	/* update the task tag in the request upiu */
	req_upiu->header.dword_0 |= cpu_to_be32(tag);

	ufshcd_prepare_req_desc_hdr(lrbp, &upiu_flags, DMA_NONE);

	/* just copy the upiu request as it is */
	memcpy(lrbp->ucd_req_ptr, req_upiu, sizeof(*lrbp->ucd_req_ptr));
	if (desc_buff && desc_op == UPIU_QUERY_OPCODE_WRITE_DESC) {
		/* The Data Segment Area is optional depending upon the query
		 * function value. for WRITE DESCRIPTOR, the data segment
		 * follows right after the tsf.
		 */
		memcpy(lrbp->ucd_req_ptr + 1, desc_buff, *buff_len);
		*buff_len = 0;
	}

	memset(lrbp->ucd_rsp_ptr, 0, sizeof(struct utp_upiu_rsp));

	hba->dev_cmd.complete = &wait;

	/* Make sure descriptors are ready before ringing the doorbell */
	wmb();
	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_send_command(hba, tag);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	/*
	 * ignore the returning value here - ufshcd_check_query_response is
	 * bound to fail since dev_cmd.query and dev_cmd.type were left empty.
	 * read the response directly ignoring all errors.
	 */
	ufshcd_wait_for_dev_cmd(hba, lrbp, QUERY_REQ_TIMEOUT);

	/* just copy the upiu response as it is */
	memcpy(rsp_upiu, lrbp->ucd_rsp_ptr, sizeof(*rsp_upiu));
	if (desc_buff && desc_op == UPIU_QUERY_OPCODE_READ_DESC) {
		u8 *descp = (u8 *)lrbp->ucd_rsp_ptr + sizeof(*rsp_upiu);
		u16 resp_len = be32_to_cpu(lrbp->ucd_rsp_ptr->header.dword_2) &
			       MASK_QUERY_DATA_SEG_LEN;

		if (*buff_len >= resp_len) {
			memcpy(desc_buff, descp, resp_len);
			*buff_len = resp_len;
		} else {
			dev_warn(hba->dev, "rsp size is bigger than buffer");
			*buff_len = 0;
			err = -EINVAL;
		}
	}

	ufshcd_put_dev_cmd_tag(hba, tag);
	wake_up(&hba->dev_cmd.tag_wq);
	up_read(&hba->clk_scaling_lock);
	return err;
}