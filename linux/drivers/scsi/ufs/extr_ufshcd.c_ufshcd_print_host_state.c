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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct ufs_hba {int /*<<< orphan*/  dev_quirks; int /*<<< orphan*/  quirks; int /*<<< orphan*/  dev; int /*<<< orphan*/  caps; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  req_abort_count; int /*<<< orphan*/  eh_flags; TYPE_2__ clk_gating; TYPE_1__* host; int /*<<< orphan*/  auto_bkops_enabled; int /*<<< orphan*/  is_sys_suspended; int /*<<< orphan*/  pm_op_in_progress; int /*<<< orphan*/  uic_link_state; int /*<<< orphan*/  curr_dev_pwr_mode; int /*<<< orphan*/  saved_uic_err; int /*<<< orphan*/  saved_err; int /*<<< orphan*/  outstanding_tasks; int /*<<< orphan*/  outstanding_reqs; int /*<<< orphan*/  lrb_in_use; int /*<<< orphan*/  ufshcd_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_self_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void ufshcd_print_host_state(struct ufs_hba *hba)
{
	dev_err(hba->dev, "UFS Host state=%d\n", hba->ufshcd_state);
	dev_err(hba->dev, "lrb in use=0x%lx, outstanding reqs=0x%lx tasks=0x%lx\n",
		hba->lrb_in_use, hba->outstanding_reqs, hba->outstanding_tasks);
	dev_err(hba->dev, "saved_err=0x%x, saved_uic_err=0x%x\n",
		hba->saved_err, hba->saved_uic_err);
	dev_err(hba->dev, "Device power mode=%d, UIC link state=%d\n",
		hba->curr_dev_pwr_mode, hba->uic_link_state);
	dev_err(hba->dev, "PM in progress=%d, sys. suspended=%d\n",
		hba->pm_op_in_progress, hba->is_sys_suspended);
	dev_err(hba->dev, "Auto BKOPS=%d, Host self-block=%d\n",
		hba->auto_bkops_enabled, hba->host->host_self_blocked);
	dev_err(hba->dev, "Clk gate=%d\n", hba->clk_gating.state);
	dev_err(hba->dev, "error handling flags=0x%x, req. abort count=%d\n",
		hba->eh_flags, hba->req_abort_count);
	dev_err(hba->dev, "Host capabilities=0x%x, caps=0x%x\n",
		hba->capabilities, hba->caps);
	dev_err(hba->dev, "quirks=0x%x, dev. quirks=0x%x\n", hba->quirks,
		hba->dev_quirks);
}