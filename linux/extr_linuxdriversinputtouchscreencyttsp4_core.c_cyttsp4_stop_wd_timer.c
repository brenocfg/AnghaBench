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
struct cyttsp4 {int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  watchdog_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  CY_WATCHDOG_TIMEOUT ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cyttsp4_stop_wd_timer(struct cyttsp4 *cd)
{
	if (!CY_WATCHDOG_TIMEOUT)
		return;

	/*
	 * Ensure we wait until the watchdog timer
	 * running on a different CPU finishes
	 */
	del_timer_sync(&cd->watchdog_timer);
	cancel_work_sync(&cd->watchdog_work);
	del_timer_sync(&cd->watchdog_timer);
}