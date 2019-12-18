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
struct sk_buff {int dummy; } ;
struct ar9170 {int /*<<< orphan*/  tx_stats_lock; int /*<<< orphan*/ * queue_stop_timeout; TYPE_2__* hw; TYPE_1__* tx_stats; int /*<<< orphan*/  tx_total_queued; } ;
struct TYPE_4__ {int queues; } ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ limit; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (TYPE_2__*,int) ; 
 int is_mem_full (struct ar9170*) ; 
 int /*<<< orphan*/  jiffies ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void carl9170_tx_accounting(struct ar9170 *ar, struct sk_buff *skb)
{
	int queue, i;
	bool mem_full;

	atomic_inc(&ar->tx_total_queued);

	queue = skb_get_queue_mapping(skb);
	spin_lock_bh(&ar->tx_stats_lock);

	/*
	 * The driver has to accept the frame, regardless if the queue is
	 * full to the brim, or not. We have to do the queuing internally,
	 * since mac80211 assumes that a driver which can operate with
	 * aggregated frames does not reject frames for this reason.
	 */
	ar->tx_stats[queue].len++;
	ar->tx_stats[queue].count++;

	mem_full = is_mem_full(ar);
	for (i = 0; i < ar->hw->queues; i++) {
		if (mem_full || ar->tx_stats[i].len >= ar->tx_stats[i].limit) {
			ieee80211_stop_queue(ar->hw, i);
			ar->queue_stop_timeout[i] = jiffies;
		}
	}

	spin_unlock_bh(&ar->tx_stats_lock);
}