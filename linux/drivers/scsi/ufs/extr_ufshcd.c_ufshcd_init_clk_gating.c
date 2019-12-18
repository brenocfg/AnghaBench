#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int mode; } ;
struct TYPE_8__ {TYPE_3__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct TYPE_6__ {int delay_ms; int is_enabled; TYPE_4__ enable_attr; TYPE_4__ delay_attr; int /*<<< orphan*/  clk_gating_workq; int /*<<< orphan*/  ungate_work; int /*<<< orphan*/  gate_work; } ;
struct ufs_hba {int /*<<< orphan*/  dev; TYPE_2__ clk_gating; TYPE_1__* host; } ;
struct TYPE_5__ {int host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_3__*) ; 
 int /*<<< orphan*/  ufshcd_clkgate_delay_show ; 
 int /*<<< orphan*/  ufshcd_clkgate_delay_store ; 
 int /*<<< orphan*/  ufshcd_clkgate_enable_show ; 
 int /*<<< orphan*/  ufshcd_clkgate_enable_store ; 
 int /*<<< orphan*/  ufshcd_gate_work ; 
 int /*<<< orphan*/  ufshcd_is_clkgating_allowed (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_ungate_work ; 

__attribute__((used)) static void ufshcd_init_clk_gating(struct ufs_hba *hba)
{
	char wq_name[sizeof("ufs_clk_gating_00")];

	if (!ufshcd_is_clkgating_allowed(hba))
		return;

	hba->clk_gating.delay_ms = 150;
	INIT_DELAYED_WORK(&hba->clk_gating.gate_work, ufshcd_gate_work);
	INIT_WORK(&hba->clk_gating.ungate_work, ufshcd_ungate_work);

	snprintf(wq_name, ARRAY_SIZE(wq_name), "ufs_clk_gating_%d",
		 hba->host->host_no);
	hba->clk_gating.clk_gating_workq = alloc_ordered_workqueue(wq_name,
							   WQ_MEM_RECLAIM);

	hba->clk_gating.is_enabled = true;

	hba->clk_gating.delay_attr.show = ufshcd_clkgate_delay_show;
	hba->clk_gating.delay_attr.store = ufshcd_clkgate_delay_store;
	sysfs_attr_init(&hba->clk_gating.delay_attr.attr);
	hba->clk_gating.delay_attr.attr.name = "clkgate_delay_ms";
	hba->clk_gating.delay_attr.attr.mode = 0644;
	if (device_create_file(hba->dev, &hba->clk_gating.delay_attr))
		dev_err(hba->dev, "Failed to create sysfs for clkgate_delay\n");

	hba->clk_gating.enable_attr.show = ufshcd_clkgate_enable_show;
	hba->clk_gating.enable_attr.store = ufshcd_clkgate_enable_store;
	sysfs_attr_init(&hba->clk_gating.enable_attr.attr);
	hba->clk_gating.enable_attr.attr.name = "clkgate_enable";
	hba->clk_gating.enable_attr.attr.mode = 0644;
	if (device_create_file(hba->dev, &hba->clk_gating.enable_attr))
		dev_err(hba->dev, "Failed to create sysfs for clkgate_enable\n");
}