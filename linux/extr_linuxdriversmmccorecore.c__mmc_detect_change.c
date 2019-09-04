#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mmc_host {int caps; int detect_change; int /*<<< orphan*/  detect; } ;

/* Variables and functions */
 int MMC_CAP_NEEDS_POLL ; 
 scalar_t__ device_can_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _mmc_detect_change(struct mmc_host *host, unsigned long delay,
				bool cd_irq)
{
	/*
	 * If the device is configured as wakeup, we prevent a new sleep for
	 * 5 s to give provision for user space to consume the event.
	 */
	if (cd_irq && !(host->caps & MMC_CAP_NEEDS_POLL) &&
		device_can_wakeup(mmc_dev(host)))
		pm_wakeup_event(mmc_dev(host), 5000);

	host->detect_change = 1;
	mmc_schedule_delayed_work(&host->detect, delay);
}