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
typedef  void* u8 ;
struct txentry_desc {int /*<<< orphan*/  header_length; int /*<<< orphan*/  flags; } ;
struct skb_frame_desc {int /*<<< orphan*/  flags; void* tx_rate_flags; void* tx_rate_idx; } ;
struct sk_buff {int dummy; } ;
struct queue_entry {int /*<<< orphan*/  flags; struct sk_buff* skb; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct ieee80211_sta {int dummy; } ;
struct data_queue {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  qid; int /*<<< orphan*/  rt2x00dev; } ;
struct TYPE_3__ {void* flags; void* idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_PROJECT ; 
 int EINVAL ; 
 int EIO ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ENTRY_DATA_PENDING ; 
 int /*<<< orphan*/  ENTRY_OWNER_DEVICE_DATA ; 
 int /*<<< orphan*/  ENTRY_TXD_ENCRYPT ; 
 int /*<<< orphan*/  ENTRY_TXD_ENCRYPT_IV ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  Q_INDEX ; 
 int /*<<< orphan*/  REQUIRE_COPY_IV ; 
 int /*<<< orphan*/  REQUIRE_DMA ; 
 int /*<<< orphan*/  REQUIRE_L2PAD ; 
 int /*<<< orphan*/  SKBDESC_NOT_MAC80211 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct skb_frame_desc* get_skb_frame_desc (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct skb_frame_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_has_cap_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00crypto_tx_copy_iv (struct sk_buff*,struct txentry_desc*) ; 
 int /*<<< orphan*/  rt2x00crypto_tx_remove_iv (struct sk_buff*,struct txentry_desc*) ; 
 int /*<<< orphan*/  rt2x00queue_align_frame (struct sk_buff*) ; 
 int /*<<< orphan*/  rt2x00queue_bar_check (struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00queue_create_tx_descriptor (int /*<<< orphan*/ ,struct sk_buff*,struct txentry_desc*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  rt2x00queue_full (struct data_queue*) ; 
 struct queue_entry* rt2x00queue_get_entry (struct data_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_index_inc (struct queue_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_insert_l2pad (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_kick_tx_queue (struct data_queue*,struct txentry_desc*) ; 
 int /*<<< orphan*/  rt2x00queue_pause_queue (struct data_queue*) ; 
 scalar_t__ rt2x00queue_threshold (struct data_queue*) ; 
 int /*<<< orphan*/  rt2x00queue_write_tx_data (struct queue_entry*,struct txentry_desc*) ; 
 int /*<<< orphan*/  rt2x00queue_write_tx_descriptor (struct queue_entry*,struct txentry_desc*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int rt2x00queue_write_tx_frame(struct data_queue *queue, struct sk_buff *skb,
			       struct ieee80211_sta *sta, bool local)
{
	struct ieee80211_tx_info *tx_info;
	struct queue_entry *entry;
	struct txentry_desc txdesc;
	struct skb_frame_desc *skbdesc;
	u8 rate_idx, rate_flags;
	int ret = 0;

	/*
	 * Copy all TX descriptor information into txdesc,
	 * after that we are free to use the skb->cb array
	 * for our information.
	 */
	rt2x00queue_create_tx_descriptor(queue->rt2x00dev, skb, &txdesc, sta);

	/*
	 * All information is retrieved from the skb->cb array,
	 * now we should claim ownership of the driver part of that
	 * array, preserving the bitrate index and flags.
	 */
	tx_info = IEEE80211_SKB_CB(skb);
	rate_idx = tx_info->control.rates[0].idx;
	rate_flags = tx_info->control.rates[0].flags;
	skbdesc = get_skb_frame_desc(skb);
	memset(skbdesc, 0, sizeof(*skbdesc));
	skbdesc->tx_rate_idx = rate_idx;
	skbdesc->tx_rate_flags = rate_flags;

	if (local)
		skbdesc->flags |= SKBDESC_NOT_MAC80211;

	/*
	 * When hardware encryption is supported, and this frame
	 * is to be encrypted, we should strip the IV/EIV data from
	 * the frame so we can provide it to the driver separately.
	 */
	if (test_bit(ENTRY_TXD_ENCRYPT, &txdesc.flags) &&
	    !test_bit(ENTRY_TXD_ENCRYPT_IV, &txdesc.flags)) {
		if (rt2x00_has_cap_flag(queue->rt2x00dev, REQUIRE_COPY_IV))
			rt2x00crypto_tx_copy_iv(skb, &txdesc);
		else
			rt2x00crypto_tx_remove_iv(skb, &txdesc);
	}

	/*
	 * When DMA allocation is required we should guarantee to the
	 * driver that the DMA is aligned to a 4-byte boundary.
	 * However some drivers require L2 padding to pad the payload
	 * rather then the header. This could be a requirement for
	 * PCI and USB devices, while header alignment only is valid
	 * for PCI devices.
	 */
	if (rt2x00_has_cap_flag(queue->rt2x00dev, REQUIRE_L2PAD))
		rt2x00queue_insert_l2pad(skb, txdesc.header_length);
	else if (rt2x00_has_cap_flag(queue->rt2x00dev, REQUIRE_DMA))
		rt2x00queue_align_frame(skb);

	/*
	 * That function must be called with bh disabled.
	 */
	spin_lock(&queue->tx_lock);

	if (unlikely(rt2x00queue_full(queue))) {
		rt2x00_dbg(queue->rt2x00dev, "Dropping frame due to full tx queue %d\n",
			   queue->qid);
		ret = -ENOBUFS;
		goto out;
	}

	entry = rt2x00queue_get_entry(queue, Q_INDEX);

	if (unlikely(test_and_set_bit(ENTRY_OWNER_DEVICE_DATA,
				      &entry->flags))) {
		rt2x00_err(queue->rt2x00dev,
			   "Arrived at non-free entry in the non-full queue %d\n"
			   "Please file bug report to %s\n",
			   queue->qid, DRV_PROJECT);
		ret = -EINVAL;
		goto out;
	}

	entry->skb = skb;

	/*
	 * It could be possible that the queue was corrupted and this
	 * call failed. Since we always return NETDEV_TX_OK to mac80211,
	 * this frame will simply be dropped.
	 */
	if (unlikely(rt2x00queue_write_tx_data(entry, &txdesc))) {
		clear_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags);
		entry->skb = NULL;
		ret = -EIO;
		goto out;
	}

	/*
	 * Put BlockAckReqs into our check list for driver BA processing.
	 */
	rt2x00queue_bar_check(entry);

	set_bit(ENTRY_DATA_PENDING, &entry->flags);

	rt2x00queue_index_inc(entry, Q_INDEX);
	rt2x00queue_write_tx_descriptor(entry, &txdesc);
	rt2x00queue_kick_tx_queue(queue, &txdesc);

out:
	/*
	 * Pausing queue has to be serialized with rt2x00lib_txdone(), so we
	 * do this under queue->tx_lock. Bottom halve was already disabled
	 * before ieee80211_xmit() call.
	 */
	if (rt2x00queue_threshold(queue))
		rt2x00queue_pause_queue(queue);

	spin_unlock(&queue->tx_lock);
	return ret;
}