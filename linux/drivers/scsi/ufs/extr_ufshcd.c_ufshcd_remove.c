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
struct TYPE_2__ {int /*<<< orphan*/  enable_attr; } ;
struct ufs_hba {TYPE_1__ clk_scaling; int /*<<< orphan*/  dev; int /*<<< orphan*/  intr_mask; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_bsg_remove (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufs_sysfs_remove_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_disable_intr (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_exit_clk_gating (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_exit_clk_scaling (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_hba_exit (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_hba_stop (struct ufs_hba*,int) ; 
 scalar_t__ ufshcd_is_clkscaling_supported (struct ufs_hba*) ; 

void ufshcd_remove(struct ufs_hba *hba)
{
	ufs_bsg_remove(hba);
	ufs_sysfs_remove_nodes(hba->dev);
	scsi_remove_host(hba->host);
	/* disable interrupts */
	ufshcd_disable_intr(hba, hba->intr_mask);
	ufshcd_hba_stop(hba, true);

	ufshcd_exit_clk_scaling(hba);
	ufshcd_exit_clk_gating(hba);
	if (ufshcd_is_clkscaling_supported(hba))
		device_remove_file(hba->dev, &hba->clk_scaling.enable_attr);
	ufshcd_hba_exit(hba);
}