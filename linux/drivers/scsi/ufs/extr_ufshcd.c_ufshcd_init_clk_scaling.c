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
typedef  int /*<<< orphan*/  wq_name ;
struct TYPE_3__ {int /*<<< orphan*/  workq; int /*<<< orphan*/  resume_work; int /*<<< orphan*/  suspend_work; } ;
struct ufs_hba {TYPE_1__ clk_scaling; TYPE_2__* host; } ;
struct TYPE_4__ {int host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  ufshcd_clk_scaling_resume_work ; 
 int /*<<< orphan*/  ufshcd_clk_scaling_suspend_work ; 
 int /*<<< orphan*/  ufshcd_clkscaling_init_sysfs (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_is_clkscaling_supported (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_init_clk_scaling(struct ufs_hba *hba)
{
	char wq_name[sizeof("ufs_clkscaling_00")];

	if (!ufshcd_is_clkscaling_supported(hba))
		return;

	INIT_WORK(&hba->clk_scaling.suspend_work,
		  ufshcd_clk_scaling_suspend_work);
	INIT_WORK(&hba->clk_scaling.resume_work,
		  ufshcd_clk_scaling_resume_work);

	snprintf(wq_name, sizeof(wq_name), "ufs_clkscaling_%d",
		 hba->host->host_no);
	hba->clk_scaling.workq = create_singlethread_workqueue(wq_name);

	ufshcd_clkscaling_init_sysfs(hba);
}