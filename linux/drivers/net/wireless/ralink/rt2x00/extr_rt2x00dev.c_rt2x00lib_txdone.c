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
typedef  int u8 ;
struct txdone_entry_desc {int /*<<< orphan*/  flags; } ;
struct skb_frame_desc {int flags; } ;
struct TYPE_5__ {int tx_success; int tx_failed; } ;
struct TYPE_6__ {TYPE_2__ qual; } ;
struct rt2x00_dev {int /*<<< orphan*/  hw; TYPE_3__ link; int /*<<< orphan*/  extra_tx_headroom; } ;
struct queue_entry {int /*<<< orphan*/  skb; TYPE_1__* queue; } ;
struct ieee80211_tx_info {int dummy; } ;
struct TYPE_4__ {struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_FRAME_TXDONE ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQUIRE_L2PAD ; 
 int /*<<< orphan*/  REQUIRE_TASKLET_CONTEXT ; 
 int SKBDESC_DESC_IN_SKB ; 
 int SKBDESC_NOT_MAC80211 ; 
 int /*<<< orphan*/  TXDONE_SUCCESS ; 
 int /*<<< orphan*/  TXDONE_UNKNOWN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 struct skb_frame_desc* get_skb_frame_desc (int /*<<< orphan*/ ) ; 
 unsigned int ieee80211_get_hdrlen_from_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_status_ni (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_has_cap_flag (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_has_cap_hw_crypto (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00crypto_tx_insert_iv (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rt2x00debug_dump_frame (struct rt2x00_dev*,int /*<<< orphan*/ ,struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00lib_clear_entry (struct rt2x00_dev*,struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00lib_fill_tx_status (struct rt2x00_dev*,struct ieee80211_tx_info*,struct skb_frame_desc*,struct txdone_entry_desc*,int) ; 
 scalar_t__ rt2x00lib_txdone_bar_status (struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00queue_remove_l2pad (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rt2x00queue_unmap_skb (struct queue_entry*) ; 
 int /*<<< orphan*/  skb_pull (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00lib_txdone(struct queue_entry *entry,
		      struct txdone_entry_desc *txdesc)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(entry->skb);
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	u8 skbdesc_flags = skbdesc->flags;
	unsigned int header_length;
	bool success;

	/*
	 * Unmap the skb.
	 */
	rt2x00queue_unmap_skb(entry);

	/*
	 * Remove the extra tx headroom from the skb.
	 */
	skb_pull(entry->skb, rt2x00dev->extra_tx_headroom);

	/*
	 * Signal that the TX descriptor is no longer in the skb.
	 */
	skbdesc->flags &= ~SKBDESC_DESC_IN_SKB;

	/*
	 * Determine the length of 802.11 header.
	 */
	header_length = ieee80211_get_hdrlen_from_skb(entry->skb);

	/*
	 * Remove L2 padding which was added during
	 */
	if (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_L2PAD))
		rt2x00queue_remove_l2pad(entry->skb, header_length);

	/*
	 * If the IV/EIV data was stripped from the frame before it was
	 * passed to the hardware, we should now reinsert it again because
	 * mac80211 will expect the same data to be present it the
	 * frame as it was passed to us.
	 */
	if (rt2x00_has_cap_hw_crypto(rt2x00dev))
		rt2x00crypto_tx_insert_iv(entry->skb, header_length);

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
	    test_bit(TXDONE_SUCCESS, &txdesc->flags) ||
	    test_bit(TXDONE_UNKNOWN, &txdesc->flags);

	/*
	 * Update TX statistics.
	 */
	rt2x00dev->link.qual.tx_success += success;
	rt2x00dev->link.qual.tx_failed += !success;

	rt2x00lib_fill_tx_status(rt2x00dev, tx_info, skbdesc, txdesc, success);

	/*
	 * Only send the status report to mac80211 when it's a frame
	 * that originated in mac80211. If this was a extra frame coming
	 * through a mac80211 library call (RTS/CTS) then we should not
	 * send the status report back.
	 */
	if (!(skbdesc_flags & SKBDESC_NOT_MAC80211)) {
		if (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_TASKLET_CONTEXT))
			ieee80211_tx_status(rt2x00dev->hw, entry->skb);
		else
			ieee80211_tx_status_ni(rt2x00dev->hw, entry->skb);
	} else {
		dev_kfree_skb_any(entry->skb);
	}

	rt2x00lib_clear_entry(rt2x00dev, entry);
}