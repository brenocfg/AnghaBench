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
struct timer_list {int dummy; } ;
struct at91wdt {scalar_t__ heartbeat; int /*<<< orphan*/  timer; int /*<<< orphan*/  wdd; int /*<<< orphan*/  next_heartbeat; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_wdt_reset (struct at91wdt*) ; 
 struct at91wdt* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ time_before (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  watchdog_active (int /*<<< orphan*/ *) ; 
 struct at91wdt* wdt ; 

__attribute__((used)) static void at91_ping(struct timer_list *t)
{
	struct at91wdt *wdt = from_timer(wdt, t, timer);
	if (time_before(jiffies, wdt->next_heartbeat) ||
	    !watchdog_active(&wdt->wdd)) {
		at91_wdt_reset(wdt);
		mod_timer(&wdt->timer, jiffies + wdt->heartbeat);
	} else {
		pr_crit("I will reset your machine !\n");
	}
}