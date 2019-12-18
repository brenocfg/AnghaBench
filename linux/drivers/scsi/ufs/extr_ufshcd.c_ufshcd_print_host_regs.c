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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  task_abort; int /*<<< orphan*/  host_reset; int /*<<< orphan*/  dev_reset; int /*<<< orphan*/  suspend_err; int /*<<< orphan*/  resume_err; int /*<<< orphan*/  link_startup_err; int /*<<< orphan*/  fatal_err; int /*<<< orphan*/  auto_hibern8_err; int /*<<< orphan*/  dme_err; int /*<<< orphan*/  tl_err; int /*<<< orphan*/  nl_err; int /*<<< orphan*/  dl_err; int /*<<< orphan*/  pa_err; int /*<<< orphan*/  hibern8_exit_cnt; int /*<<< orphan*/  last_hibern8_exit_tstamp; } ;
struct ufs_hba {TYPE_2__* vops; TYPE_1__ ufs_stats; int /*<<< orphan*/  dev; scalar_t__ outstanding_tasks; scalar_t__ outstanding_reqs; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  ufs_version; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dbg_register_dump ) (struct ufs_hba*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  UFSHCI_REG_SPACE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_dump_regs (struct ufs_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ufshcd_print_clk_freqs (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_print_err_hist (struct ufs_hba*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void ufshcd_print_host_regs(struct ufs_hba *hba)
{
	ufshcd_dump_regs(hba, 0, UFSHCI_REG_SPACE_SIZE, "host_regs: ");
	dev_err(hba->dev, "hba->ufs_version = 0x%x, hba->capabilities = 0x%x\n",
		hba->ufs_version, hba->capabilities);
	dev_err(hba->dev,
		"hba->outstanding_reqs = 0x%x, hba->outstanding_tasks = 0x%x\n",
		(u32)hba->outstanding_reqs, (u32)hba->outstanding_tasks);
	dev_err(hba->dev,
		"last_hibern8_exit_tstamp at %lld us, hibern8_exit_cnt = %d\n",
		ktime_to_us(hba->ufs_stats.last_hibern8_exit_tstamp),
		hba->ufs_stats.hibern8_exit_cnt);

	ufshcd_print_err_hist(hba, &hba->ufs_stats.pa_err, "pa_err");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.dl_err, "dl_err");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.nl_err, "nl_err");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.tl_err, "tl_err");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.dme_err, "dme_err");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.auto_hibern8_err,
			      "auto_hibern8_err");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.fatal_err, "fatal_err");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.link_startup_err,
			      "link_startup_fail");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.resume_err, "resume_fail");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.suspend_err,
			      "suspend_fail");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.dev_reset, "dev_reset");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.host_reset, "host_reset");
	ufshcd_print_err_hist(hba, &hba->ufs_stats.task_abort, "task_abort");

	ufshcd_print_clk_freqs(hba);

	if (hba->vops && hba->vops->dbg_register_dump)
		hba->vops->dbg_register_dump(hba);
}