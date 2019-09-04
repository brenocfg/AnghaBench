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
typedef  int u32 ;
struct prcmu_auto_pm_config {int sva_auto_pm_enable; int sia_auto_pm_enable; int sva_power_on; int sia_power_on; int sva_policy; int sia_policy; } ;
struct TYPE_2__ {int auto_pm_enabled; int /*<<< orphan*/  auto_pm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PRCMU_AUTO_PM_ON ; 
 scalar_t__ PRCM_REQ_MB2_AUTO_PM_IDLE ; 
 scalar_t__ PRCM_REQ_MB2_AUTO_PM_SLEEP ; 
 TYPE_1__ mb2_transfer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void prcmu_configure_auto_pm(struct prcmu_auto_pm_config *sleep,
	struct prcmu_auto_pm_config *idle)
{
	u32 sleep_cfg;
	u32 idle_cfg;
	unsigned long flags;

	BUG_ON((sleep == NULL) || (idle == NULL));

	sleep_cfg = (sleep->sva_auto_pm_enable & 0xF);
	sleep_cfg = ((sleep_cfg << 4) | (sleep->sia_auto_pm_enable & 0xF));
	sleep_cfg = ((sleep_cfg << 8) | (sleep->sva_power_on & 0xFF));
	sleep_cfg = ((sleep_cfg << 8) | (sleep->sia_power_on & 0xFF));
	sleep_cfg = ((sleep_cfg << 4) | (sleep->sva_policy & 0xF));
	sleep_cfg = ((sleep_cfg << 4) | (sleep->sia_policy & 0xF));

	idle_cfg = (idle->sva_auto_pm_enable & 0xF);
	idle_cfg = ((idle_cfg << 4) | (idle->sia_auto_pm_enable & 0xF));
	idle_cfg = ((idle_cfg << 8) | (idle->sva_power_on & 0xFF));
	idle_cfg = ((idle_cfg << 8) | (idle->sia_power_on & 0xFF));
	idle_cfg = ((idle_cfg << 4) | (idle->sva_policy & 0xF));
	idle_cfg = ((idle_cfg << 4) | (idle->sia_policy & 0xF));

	spin_lock_irqsave(&mb2_transfer.auto_pm_lock, flags);

	/*
	 * The autonomous power management configuration is done through
	 * fields in mailbox 2, but these fields are only used as shared
	 * variables - i.e. there is no need to send a message.
	 */
	writel(sleep_cfg, (tcdm_base + PRCM_REQ_MB2_AUTO_PM_SLEEP));
	writel(idle_cfg, (tcdm_base + PRCM_REQ_MB2_AUTO_PM_IDLE));

	mb2_transfer.auto_pm_enabled =
		((sleep->sva_auto_pm_enable == PRCMU_AUTO_PM_ON) ||
		 (sleep->sia_auto_pm_enable == PRCMU_AUTO_PM_ON) ||
		 (idle->sva_auto_pm_enable == PRCMU_AUTO_PM_ON) ||
		 (idle->sia_auto_pm_enable == PRCMU_AUTO_PM_ON));

	spin_unlock_irqrestore(&mb2_transfer.auto_pm_lock, flags);
}