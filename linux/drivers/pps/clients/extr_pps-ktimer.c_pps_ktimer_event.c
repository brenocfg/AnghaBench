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
struct pps_event_time {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  PPS_CAPTUREASSERT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktimer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pps ; 
 int /*<<< orphan*/  pps_event (int /*<<< orphan*/ ,struct pps_event_time*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pps_get_ts (struct pps_event_time*) ; 

__attribute__((used)) static void pps_ktimer_event(struct timer_list *unused)
{
	struct pps_event_time ts;

	/* First of all we get the time stamp... */
	pps_get_ts(&ts);

	pps_event(pps, &ts, PPS_CAPTUREASSERT, NULL);

	mod_timer(&ktimer, jiffies + HZ);
}