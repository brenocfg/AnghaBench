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
struct rt2x00_dev {int /*<<< orphan*/  bar_list_lock; int /*<<< orphan*/  bar_list; scalar_t__ extra_tx_headroom; } ;
struct rt2x00_bar_list_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  start_seq_num; int /*<<< orphan*/  control; int /*<<< orphan*/  ta; int /*<<< orphan*/  ra; scalar_t__ block_acked; struct queue_entry* entry; } ;
struct queue_entry {TYPE_2__* skb; TYPE_1__* queue; } ;
struct ieee80211_bar {int /*<<< orphan*/  start_seq_num; int /*<<< orphan*/  control; int /*<<< orphan*/  ta; int /*<<< orphan*/  ra; int /*<<< orphan*/  frame_control; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 struct rt2x00_bar_list_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2x00queue_bar_check(struct queue_entry *entry)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	struct ieee80211_bar *bar = (void *) (entry->skb->data +
				    rt2x00dev->extra_tx_headroom);
	struct rt2x00_bar_list_entry *bar_entry;

	if (likely(!ieee80211_is_back_req(bar->frame_control)))
		return;

	bar_entry = kmalloc(sizeof(*bar_entry), GFP_ATOMIC);

	/*
	 * If the alloc fails we still send the BAR out but just don't track
	 * it in our bar list. And as a result we will report it to mac80211
	 * back as failed.
	 */
	if (!bar_entry)
		return;

	bar_entry->entry = entry;
	bar_entry->block_acked = 0;

	/*
	 * Copy the relevant parts of the 802.11 BAR into out check list
	 * such that we can use RCU for less-overhead in the RX path since
	 * sending BARs and processing the according BlockAck should be
	 * the exception.
	 */
	memcpy(bar_entry->ra, bar->ra, sizeof(bar->ra));
	memcpy(bar_entry->ta, bar->ta, sizeof(bar->ta));
	bar_entry->control = bar->control;
	bar_entry->start_seq_num = bar->start_seq_num;

	/*
	 * Insert BAR into our BAR check list.
	 */
	spin_lock_bh(&rt2x00dev->bar_list_lock);
	list_add_tail_rcu(&bar_entry->list, &rt2x00dev->bar_list);
	spin_unlock_bh(&rt2x00dev->bar_list_lock);
}