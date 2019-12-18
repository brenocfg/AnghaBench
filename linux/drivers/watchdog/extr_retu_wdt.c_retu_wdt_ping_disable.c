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
struct retu_wdt_dev {int /*<<< orphan*/  ping_work; int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETU_REG_WATCHDOG ; 
 int /*<<< orphan*/  RETU_WDT_MAX_TIMER ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void retu_wdt_ping_disable(struct retu_wdt_dev *wdev)
{
	retu_write(wdev->rdev, RETU_REG_WATCHDOG, RETU_WDT_MAX_TIMER);
	cancel_delayed_work_sync(&wdev->ping_work);
}