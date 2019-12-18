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
typedef  scalar_t__ u32 ;
struct ufs_hba {scalar_t__ ahit; TYPE_1__* host; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AUTO_HIBERNATE_IDLE_TIMER ; 
 int /*<<< orphan*/  pm_runtime_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ufshcd_is_auto_hibern8_supported (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_writel (struct ufs_hba*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufshcd_auto_hibern8_update(struct ufs_hba *hba, u32 ahit)
{
	unsigned long flags;

	if (!ufshcd_is_auto_hibern8_supported(hba))
		return;

	spin_lock_irqsave(hba->host->host_lock, flags);
	if (hba->ahit == ahit)
		goto out_unlock;
	hba->ahit = ahit;
	if (!pm_runtime_suspended(hba->dev))
		ufshcd_writel(hba, hba->ahit, REG_AUTO_HIBERNATE_IDLE_TIMER);
out_unlock:
	spin_unlock_irqrestore(hba->host->host_lock, flags);
}