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
struct wakeup_source {int /*<<< orphan*/  active; int /*<<< orphan*/  wakeup_count; int /*<<< orphan*/  event_count; } ;

/* Variables and functions */
 scalar_t__ events_check_enabled ; 
 int /*<<< orphan*/  pm_system_wakeup () ; 
 int /*<<< orphan*/  wakeup_source_activate (struct wakeup_source*) ; 

__attribute__((used)) static void wakeup_source_report_event(struct wakeup_source *ws, bool hard)
{
	ws->event_count++;
	/* This is racy, but the counter is approximate anyway. */
	if (events_check_enabled)
		ws->wakeup_count++;

	if (!ws->active)
		wakeup_source_activate(ws);

	if (hard)
		pm_system_wakeup();
}