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
struct wl1271 {int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/ * queue_stop_reasons; } ;
typedef  enum wlcore_queue_stop_reason { ____Placeholder_wlcore_queue_stop_reason } wlcore_queue_stop_reason ;

/* Variables and functions */
 int NUM_TX_QUEUES ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int WLCORE_NUM_MAC_ADDRESSES ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ *) ; 

void wlcore_wake_queues(struct wl1271 *wl,
			enum wlcore_queue_stop_reason reason)
{
	int i;
	unsigned long flags;

	spin_lock_irqsave(&wl->wl_lock, flags);

	/* mark all possible queues as awake */
        for (i = 0; i < WLCORE_NUM_MAC_ADDRESSES * NUM_TX_QUEUES; i++)
		WARN_ON_ONCE(!test_and_clear_bit(reason,
						 &wl->queue_stop_reasons[i]));

	/* use the global version to make sure all vifs in mac80211 we don't
	 * know are woken up.
	 */
	ieee80211_wake_queues(wl->hw);

	spin_unlock_irqrestore(&wl->wl_lock, flags);
}