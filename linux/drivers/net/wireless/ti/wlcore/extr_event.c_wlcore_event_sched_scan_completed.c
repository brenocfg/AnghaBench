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
typedef  int /*<<< orphan*/  u8 ;
struct wl1271 {int /*<<< orphan*/ * sched_vif; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int /*<<< orphan*/  ieee80211_sched_scan_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void wlcore_event_sched_scan_completed(struct wl1271 *wl,
				       u8 status)
{
	wl1271_debug(DEBUG_EVENT, "PERIODIC_SCAN_COMPLETE_EVENT (status 0x%0x)",
		     status);

	if (wl->sched_vif) {
		ieee80211_sched_scan_stopped(wl->hw);
		wl->sched_vif = NULL;
	}
}