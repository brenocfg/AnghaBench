#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ufshcd_lrb {scalar_t__ cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  tag_wq; struct completion* complete; } ;
struct ufs_hba {int /*<<< orphan*/  clk_scaling_lock; TYPE_2__ dev_cmd; TYPE_1__* host; struct ufshcd_lrb* lrb; } ;
struct completion {int dummy; } ;
typedef  enum dev_cmd_type { ____Placeholder_dev_cmd_type } dev_cmd_type ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ufshcd_add_query_upiu_trace (struct ufs_hba*,int,char*) ; 
 int ufshcd_compose_dev_cmd (struct ufs_hba*,struct ufshcd_lrb*,int,int) ; 
 int /*<<< orphan*/  ufshcd_get_dev_cmd_tag (struct ufs_hba*,int*) ; 
 int /*<<< orphan*/  ufshcd_put_dev_cmd_tag (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_send_command (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_vops_setup_xfer_req (struct ufs_hba*,int,int) ; 
 int ufshcd_wait_for_dev_cmd (struct ufs_hba*,struct ufshcd_lrb*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ufshcd_exec_dev_cmd(struct ufs_hba *hba,
		enum dev_cmd_type cmd_type, int timeout)
{
	struct ufshcd_lrb *lrbp;
	int err;
	int tag;
	struct completion wait;
	unsigned long flags;

	down_read(&hba->clk_scaling_lock);

	/*
	 * Get free slot, sleep if slots are unavailable.
	 * Even though we use wait_event() which sleeps indefinitely,
	 * the maximum wait time is bounded by SCSI request timeout.
	 */
	wait_event(hba->dev_cmd.tag_wq, ufshcd_get_dev_cmd_tag(hba, &tag));

	init_completion(&wait);
	lrbp = &hba->lrb[tag];
	WARN_ON(lrbp->cmd);
	err = ufshcd_compose_dev_cmd(hba, lrbp, cmd_type, tag);
	if (unlikely(err))
		goto out_put_tag;

	hba->dev_cmd.complete = &wait;

	ufshcd_add_query_upiu_trace(hba, tag, "query_send");
	/* Make sure descriptors are ready before ringing the doorbell */
	wmb();
	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_vops_setup_xfer_req(hba, tag, (lrbp->cmd ? true : false));
	ufshcd_send_command(hba, tag);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	err = ufshcd_wait_for_dev_cmd(hba, lrbp, timeout);

	ufshcd_add_query_upiu_trace(hba, tag,
			err ? "query_complete_err" : "query_complete");

out_put_tag:
	ufshcd_put_dev_cmd_tag(hba, tag);
	wake_up(&hba->dev_cmd.tag_wq);
	up_read(&hba->clk_scaling_lock);
	return err;
}