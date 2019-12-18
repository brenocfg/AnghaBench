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
struct rtsx_pcr {scalar_t__ state; int /*<<< orphan*/  idle_work; TYPE_1__* ops; scalar_t__ remove_pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_auto_blink ) (struct rtsx_pcr*) ;} ;

/* Variables and functions */
 scalar_t__ PDEV_STAT_RUN ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  rtsx_pm_full_on (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  stub1 (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  system_wq ; 

void rtsx_pci_start_run(struct rtsx_pcr *pcr)
{
	/* If pci device removed, don't queue idle work any more */
	if (pcr->remove_pci)
		return;

	if (pcr->state != PDEV_STAT_RUN) {
		pcr->state = PDEV_STAT_RUN;
		if (pcr->ops->enable_auto_blink)
			pcr->ops->enable_auto_blink(pcr);
		rtsx_pm_full_on(pcr);
	}

	mod_delayed_work(system_wq, &pcr->idle_work, msecs_to_jiffies(200));
}