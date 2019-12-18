#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct txdone_entry_desc {int /*<<< orphan*/  flags; } ;
struct skb_frame_desc {int /*<<< orphan*/  sta; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int tx_success; int tx_failed; } ;
struct TYPE_6__ {TYPE_2__ qual; } ;
struct rt2x00_dev {int /*<<< orphan*/  hw; TYPE_3__ link; } ;
struct queue_entry {int /*<<< orphan*/  skb; TYPE_1__* queue; } ;
struct ieee80211_tx_info {int dummy; } ;
struct TYPE_4__ {struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_FRAME_TXDONE ; 
 int /*<<< orphan*/  SKBDESC_DESC_IN_SKB ; 
 int /*<<< orphan*/  TXDONE_SUCCESS ; 
 int /*<<< orphan*/  TXDONE_UNKNOWN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 struct skb_frame_desc* get_skb_frame_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_status_noskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  rt2x00debug_dump_frame (struct rt2x00_dev*,int /*<<< orphan*/ ,struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00lib_clear_entry (struct rt2x00_dev*,struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00lib_fill_tx_status (struct rt2x00_dev*,struct ieee80211_tx_info*,struct skb_frame_desc*,struct txdone_entry_desc*,int) ; 
 scalar_t__ rt2x00lib_txdone_bar_status (struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00queue_unmap_skb (struct queue_entry*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00lib_txdone_nomatch(struct queue_entry *entry,
			      struct txdone_entry_desc *txdesc)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	struct ieee80211_tx_info txinfo = {};
	bool success;

	/*
	 * Unmap the skb.
	 */
	rt2x00queue_unmap_skb(entry);

	/*
	 * Signal that the TX descriptor is no longer in the skb.
	 */
	skbdesc->flags &= ~SKBDESC_DESC_IN_SKB;

	/*
	 * Send frame to debugfs immediately, after this call is completed
	 * we are going to overwrite the skb->cb array.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_TXDONE, entry);

	/*
	 * Determine if the frame has been successfully transmitted and
	 * remove BARs from our check list while checking for their
	 * TX status.
	 */
	success =
	    rt2x00lib_txdone_bar_status(entry) ||
	    test_bit(TXDONE_SUCCESS, &txdesc->flags);

	if (!test_bit(TXDONE_UNKNOWN, &txdesc->flags)) {
		/*
		 * Update TX statistics.
		 */
		rt2x00dev->link.qual.tx_success += success;
		rt2x00dev->link.qual.tx_failed += !success;

		rt2x00lib_fill_tx_status(rt2x00dev, &txinfo, skbdesc, txdesc,
					 success);
		ieee80211_tx_status_noskb(rt2x00dev->hw, skbdesc->sta, &txinfo);
	}

	dev_kfree_skb_any(entry->skb);
	rt2x00lib_clear_entry(rt2x00dev, entry);
}