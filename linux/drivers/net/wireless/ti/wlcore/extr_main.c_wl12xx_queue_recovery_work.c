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
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WL1271_FLAG_INTENDED_FW_RECOVERY ; 
 int /*<<< orphan*/  WL1271_FLAG_RECOVERY_IN_PROGRESS ; 
 scalar_t__ WLCORE_STATE_ON ; 
 scalar_t__ WLCORE_STATE_RESTARTING ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void wl12xx_queue_recovery_work(struct wl1271 *wl)
{
	/* Avoid a recursive recovery */
	if (wl->state == WLCORE_STATE_ON) {
		WARN_ON(!test_bit(WL1271_FLAG_INTENDED_FW_RECOVERY,
				  &wl->flags));

		wl->state = WLCORE_STATE_RESTARTING;
		set_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags);
		ieee80211_queue_work(wl->hw, &wl->recovery_work);
	}
}