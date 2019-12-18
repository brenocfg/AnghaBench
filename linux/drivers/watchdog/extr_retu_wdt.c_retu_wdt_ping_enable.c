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
 int HZ ; 
 int /*<<< orphan*/  RETU_REG_WATCHDOG ; 
 int RETU_WDT_MAX_TIMER ; 
 int /*<<< orphan*/  retu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  round_jiffies_relative (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void retu_wdt_ping_enable(struct retu_wdt_dev *wdev)
{
	retu_write(wdev->rdev, RETU_REG_WATCHDOG, RETU_WDT_MAX_TIMER);
	schedule_delayed_work(&wdev->ping_work,
			round_jiffies_relative(RETU_WDT_MAX_TIMER * HZ / 2));
}