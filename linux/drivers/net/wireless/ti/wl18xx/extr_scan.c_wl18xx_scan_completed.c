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
struct wl12xx_vif {int dummy; } ;
struct TYPE_2__ {int failed; } ;
struct wl1271 {int /*<<< orphan*/  scan_complete_work; int /*<<< orphan*/  hw; TYPE_1__ scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void wl18xx_scan_completed(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	wl->scan.failed = false;
	cancel_delayed_work(&wl->scan_complete_work);
	ieee80211_queue_delayed_work(wl->hw, &wl->scan_complete_work,
				     msecs_to_jiffies(0));
}