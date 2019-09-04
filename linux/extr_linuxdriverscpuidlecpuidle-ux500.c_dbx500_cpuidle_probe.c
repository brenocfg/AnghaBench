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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABB ; 
 int /*<<< orphan*/  ARM ; 
 int PRCMU_WAKEUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC ; 
 int cpuidle_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prcmu_enable_wakeups (int) ; 
 int /*<<< orphan*/  ux500_idle_driver ; 

__attribute__((used)) static int dbx500_cpuidle_probe(struct platform_device *pdev)
{
	/* Configure wake up reasons */
	prcmu_enable_wakeups(PRCMU_WAKEUP(ARM) | PRCMU_WAKEUP(RTC) |
			     PRCMU_WAKEUP(ABB));

	return cpuidle_register(&ux500_idle_driver, NULL);
}