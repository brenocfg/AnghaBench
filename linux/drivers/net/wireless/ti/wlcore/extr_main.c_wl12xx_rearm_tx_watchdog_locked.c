#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tx_watchdog_timeout; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct wl1271 {scalar_t__ tx_allocated_blocks; TYPE_2__ conf; int /*<<< orphan*/  tx_watchdog_work; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void wl12xx_rearm_tx_watchdog_locked(struct wl1271 *wl)
{
	/* if the watchdog is not armed, don't do anything */
	if (wl->tx_allocated_blocks == 0)
		return;

	cancel_delayed_work(&wl->tx_watchdog_work);
	ieee80211_queue_delayed_work(wl->hw, &wl->tx_watchdog_work,
		msecs_to_jiffies(wl->conf.tx.tx_watchdog_timeout));
}