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
struct ufs_hba {int /*<<< orphan*/  outstanding_reqs; TYPE_1__* lrb; } ;
struct TYPE_2__ {int /*<<< orphan*/  compl_time_stamp; int /*<<< orphan*/  issue_time_stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_UTP_TRANSFER_REQ_DOOR_BELL ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_add_command_trace (struct ufs_hba*,unsigned int,char*) ; 
 int /*<<< orphan*/  ufshcd_clk_scaling_start_busy (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_writel (struct ufs_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline
void ufshcd_send_command(struct ufs_hba *hba, unsigned int task_tag)
{
	hba->lrb[task_tag].issue_time_stamp = ktime_get();
	hba->lrb[task_tag].compl_time_stamp = ktime_set(0, 0);
	ufshcd_clk_scaling_start_busy(hba);
	__set_bit(task_tag, &hba->outstanding_reqs);
	ufshcd_writel(hba, 1 << task_tag, REG_UTP_TRANSFER_REQ_DOOR_BELL);
	/* Make sure that doorbell is committed immediately */
	wmb();
	ufshcd_add_command_trace(hba, task_tag, "send");
}