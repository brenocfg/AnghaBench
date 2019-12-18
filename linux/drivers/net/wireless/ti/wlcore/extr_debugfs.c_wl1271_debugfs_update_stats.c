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
struct TYPE_2__ {scalar_t__ fw_stats_update; int /*<<< orphan*/  fw_stats; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; TYPE_1__ stats; int /*<<< orphan*/  plt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL1271_DEBUGFS_STATS_LIFETIME ; 
 scalar_t__ WLCORE_STATE_ON ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_acx_statistics (struct wl1271*,int /*<<< orphan*/ ) ; 

void wl1271_debugfs_update_stats(struct wl1271 *wl)
{
	int ret;

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out;
	}

	if (!wl->plt &&
	    time_after(jiffies, wl->stats.fw_stats_update +
		       msecs_to_jiffies(WL1271_DEBUGFS_STATS_LIFETIME))) {
		wl1271_acx_statistics(wl, wl->stats.fw_stats);
		wl->stats.fw_stats_update = jiffies;
	}

	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
}