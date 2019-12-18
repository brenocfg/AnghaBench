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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int /*<<< orphan*/  hw; int /*<<< orphan*/ * queue_stop_reasons; } ;
typedef  enum wlcore_queue_stop_reason { ____Placeholder_wlcore_queue_stop_reason } wlcore_queue_stop_reason ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 int wlcore_tx_get_mac80211_queue (struct wl12xx_vif*,int /*<<< orphan*/ ) ; 

void wlcore_stop_queue_locked(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			      u8 queue, enum wlcore_queue_stop_reason reason)
{
	int hwq = wlcore_tx_get_mac80211_queue(wlvif, queue);
	bool stopped = !!wl->queue_stop_reasons[hwq];

	/* queue should not be stopped for this reason */
	WARN_ON_ONCE(test_and_set_bit(reason, &wl->queue_stop_reasons[hwq]));

	if (stopped)
		return;

	ieee80211_stop_queue(wl->hw, hwq);
}