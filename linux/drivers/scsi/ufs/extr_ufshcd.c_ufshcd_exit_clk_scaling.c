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
struct TYPE_2__ {int /*<<< orphan*/  workq; } ;
struct ufs_hba {TYPE_1__ clk_scaling; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_devfreq_remove (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_is_clkscaling_supported (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_exit_clk_scaling(struct ufs_hba *hba)
{
	if (!ufshcd_is_clkscaling_supported(hba))
		return;

	destroy_workqueue(hba->clk_scaling.workq);
	ufshcd_devfreq_remove(hba);
}