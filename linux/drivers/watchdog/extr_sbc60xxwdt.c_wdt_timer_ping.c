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

/* Variables and functions */
 scalar_t__ WDT_INTERVAL ; 
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  next_heartbeat ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ time_before (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  wdt_start ; 

__attribute__((used)) static void wdt_timer_ping(struct timer_list *unused)
{
	/* If we got a heartbeat pulse within the WDT_US_INTERVAL
	 * we agree to ping the WDT
	 */
	if (time_before(jiffies, next_heartbeat)) {
		/* Ping the WDT by reading from wdt_start */
		inb_p(wdt_start);
		/* Re-set the timer interval */
		mod_timer(&timer, jiffies + WDT_INTERVAL);
	} else
		pr_warn("Heartbeat lost! Will not ping the watchdog\n");
}