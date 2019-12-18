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
struct TYPE_3__ {int is_suspended; } ;
struct ufs_hba {TYPE_2__* host; TYPE_1__ clk_scaling; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ufshcd_suspend_clkscaling (struct ufs_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ufshcd_is_clkscaling_supported (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_suspend_clkscaling(struct ufs_hba *hba)
{
	unsigned long flags;
	bool suspend = false;

	if (!ufshcd_is_clkscaling_supported(hba))
		return;

	spin_lock_irqsave(hba->host->host_lock, flags);
	if (!hba->clk_scaling.is_suspended) {
		suspend = true;
		hba->clk_scaling.is_suspended = true;
	}
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	if (suspend)
		__ufshcd_suspend_clkscaling(hba);
}