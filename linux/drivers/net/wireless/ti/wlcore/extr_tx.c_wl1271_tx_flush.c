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
struct wl1271 {scalar_t__ tx_frames_cnt; int num_links; int /*<<< orphan*/  flush_mutex; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tx_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int WL1271_TX_FLUSH_TIMEOUT ; 
 int /*<<< orphan*/  WLCORE_QUEUE_STOP_REASON_FLUSH ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 
 unsigned long usecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wl1271_tx_reset_link_queues (struct wl1271*,int) ; 
 scalar_t__ wl1271_tx_total_queue_count (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_tx_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 
 int /*<<< orphan*/  wlcore_stop_queues (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_wake_queues (struct wl1271*,int /*<<< orphan*/ ) ; 

void wl1271_tx_flush(struct wl1271 *wl)
{
	unsigned long timeout, start_time;
	int i;
	start_time = jiffies;
	timeout = start_time + usecs_to_jiffies(WL1271_TX_FLUSH_TIMEOUT);

	/* only one flush should be in progress, for consistent queue state */
	mutex_lock(&wl->flush_mutex);

	mutex_lock(&wl->mutex);
	if (wl->tx_frames_cnt == 0 && wl1271_tx_total_queue_count(wl) == 0) {
		mutex_unlock(&wl->mutex);
		goto out;
	}

	wlcore_stop_queues(wl, WLCORE_QUEUE_STOP_REASON_FLUSH);

	while (!time_after(jiffies, timeout)) {
		wl1271_debug(DEBUG_MAC80211, "flushing tx buffer: %d %d",
			     wl->tx_frames_cnt,
			     wl1271_tx_total_queue_count(wl));

		/* force Tx and give the driver some time to flush data */
		mutex_unlock(&wl->mutex);
		if (wl1271_tx_total_queue_count(wl))
			wl1271_tx_work(&wl->tx_work);
		msleep(20);
		mutex_lock(&wl->mutex);

		if ((wl->tx_frames_cnt == 0) &&
		    (wl1271_tx_total_queue_count(wl) == 0)) {
			wl1271_debug(DEBUG_MAC80211, "tx flush took %d ms",
				     jiffies_to_msecs(jiffies - start_time));
			goto out_wake;
		}
	}

	wl1271_warning("Unable to flush all TX buffers, "
		       "timed out (timeout %d ms",
		       WL1271_TX_FLUSH_TIMEOUT / 1000);

	/* forcibly flush all Tx buffers on our queues */
	for (i = 0; i < wl->num_links; i++)
		wl1271_tx_reset_link_queues(wl, i);

out_wake:
	wlcore_wake_queues(wl, WLCORE_QUEUE_STOP_REASON_FLUSH);
	mutex_unlock(&wl->mutex);
out:
	mutex_unlock(&wl->flush_mutex);
}