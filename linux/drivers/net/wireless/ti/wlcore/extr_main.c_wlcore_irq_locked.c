#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct wl1271 {int irq_flags; scalar_t__ state; int watchdog_recovery; int /*<<< orphan*/  dev; int /*<<< orphan*/  deferred_rx_queue; int /*<<< orphan*/  deferred_tx_queue; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  flags; TYPE_1__* fw_status; } ;
struct TYPE_3__ {int intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_IRQ ; 
 int EIO ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int WL1271_ACX_INTR_DATA ; 
 int WL1271_ACX_INTR_EVENT_A ; 
 int WL1271_ACX_INTR_EVENT_B ; 
 int WL1271_ACX_INTR_HW_AVAILABLE ; 
 int WL1271_ACX_INTR_INIT_COMPLETE ; 
 int WL1271_ACX_INTR_WATCHDOG ; 
 int WL1271_ACX_SW_INTR_WATCHDOG ; 
 unsigned int WL1271_DEFERRED_QUEUE_LIMIT ; 
 int /*<<< orphan*/  WL1271_FLAG_FW_TX_BUSY ; 
 int /*<<< orphan*/  WL1271_FLAG_IRQ_RUNNING ; 
 int WL1271_IRQ_MAX_LOOPS ; 
 int WLCORE_ALL_INTR_MASK ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 unsigned int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int wl1271_event_handle (struct wl1271*,int) ; 
 int /*<<< orphan*/  wl1271_flush_deferred_work (struct wl1271*) ; 
 scalar_t__ wl1271_tx_total_queue_count (struct wl1271*) ; 
 int wlcore_fw_status (struct wl1271*,TYPE_1__*) ; 
 int wlcore_hw_tx_delayed_compl (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_hw_tx_immediate_compl (struct wl1271*) ; 
 int wlcore_rx (struct wl1271*,TYPE_1__*) ; 
 int wlcore_tx_work_locked (struct wl1271*) ; 

__attribute__((used)) static int wlcore_irq_locked(struct wl1271 *wl)
{
	int ret = 0;
	u32 intr;
	int loopcount = WL1271_IRQ_MAX_LOOPS;
	bool done = false;
	unsigned int defer_count;
	unsigned long flags;

	/*
	 * In case edge triggered interrupt must be used, we cannot iterate
	 * more than once without introducing race conditions with the hardirq.
	 */
	if (wl->irq_flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))
		loopcount = 1;

	wl1271_debug(DEBUG_IRQ, "IRQ work");

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out;
	}

	while (!done && loopcount--) {
		/*
		 * In order to avoid a race with the hardirq, clear the flag
		 * before acknowledging the chip.
		 */
		clear_bit(WL1271_FLAG_IRQ_RUNNING, &wl->flags);
		smp_mb__after_atomic();

		ret = wlcore_fw_status(wl, wl->fw_status);
		if (ret < 0)
			goto out;

		wlcore_hw_tx_immediate_compl(wl);

		intr = wl->fw_status->intr;
		intr &= WLCORE_ALL_INTR_MASK;
		if (!intr) {
			done = true;
			continue;
		}

		if (unlikely(intr & WL1271_ACX_INTR_WATCHDOG)) {
			wl1271_error("HW watchdog interrupt received! starting recovery.");
			wl->watchdog_recovery = true;
			ret = -EIO;

			/* restarting the chip. ignore any other interrupt. */
			goto out;
		}

		if (unlikely(intr & WL1271_ACX_SW_INTR_WATCHDOG)) {
			wl1271_error("SW watchdog interrupt received! "
				     "starting recovery.");
			wl->watchdog_recovery = true;
			ret = -EIO;

			/* restarting the chip. ignore any other interrupt. */
			goto out;
		}

		if (likely(intr & WL1271_ACX_INTR_DATA)) {
			wl1271_debug(DEBUG_IRQ, "WL1271_ACX_INTR_DATA");

			ret = wlcore_rx(wl, wl->fw_status);
			if (ret < 0)
				goto out;

			/* Check if any tx blocks were freed */
			spin_lock_irqsave(&wl->wl_lock, flags);
			if (!test_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags) &&
			    wl1271_tx_total_queue_count(wl) > 0) {
				spin_unlock_irqrestore(&wl->wl_lock, flags);
				/*
				 * In order to avoid starvation of the TX path,
				 * call the work function directly.
				 */
				ret = wlcore_tx_work_locked(wl);
				if (ret < 0)
					goto out;
			} else {
				spin_unlock_irqrestore(&wl->wl_lock, flags);
			}

			/* check for tx results */
			ret = wlcore_hw_tx_delayed_compl(wl);
			if (ret < 0)
				goto out;

			/* Make sure the deferred queues don't get too long */
			defer_count = skb_queue_len(&wl->deferred_tx_queue) +
				      skb_queue_len(&wl->deferred_rx_queue);
			if (defer_count > WL1271_DEFERRED_QUEUE_LIMIT)
				wl1271_flush_deferred_work(wl);
		}

		if (intr & WL1271_ACX_INTR_EVENT_A) {
			wl1271_debug(DEBUG_IRQ, "WL1271_ACX_INTR_EVENT_A");
			ret = wl1271_event_handle(wl, 0);
			if (ret < 0)
				goto out;
		}

		if (intr & WL1271_ACX_INTR_EVENT_B) {
			wl1271_debug(DEBUG_IRQ, "WL1271_ACX_INTR_EVENT_B");
			ret = wl1271_event_handle(wl, 1);
			if (ret < 0)
				goto out;
		}

		if (intr & WL1271_ACX_INTR_INIT_COMPLETE)
			wl1271_debug(DEBUG_IRQ,
				     "WL1271_ACX_INTR_INIT_COMPLETE");

		if (intr & WL1271_ACX_INTR_HW_AVAILABLE)
			wl1271_debug(DEBUG_IRQ, "WL1271_ACX_INTR_HW_AVAILABLE");
	}

	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);

out:
	return ret;
}