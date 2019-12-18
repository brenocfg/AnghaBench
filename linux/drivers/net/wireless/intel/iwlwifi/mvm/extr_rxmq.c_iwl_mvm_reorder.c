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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;
struct iwl_rx_mpdu_desc {int mac_flags2; int amsdu_info; int /*<<< orphan*/  reorder_data; } ;
struct iwl_mvm_sta {scalar_t__ sta_id; } ;
struct iwl_mvm_reorder_buffer {int valid; int head_sn; int buf_size; int last_amsdu; size_t last_sub_index; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_stored; } ;
struct TYPE_2__ {int /*<<< orphan*/  reorder_time; int /*<<< orphan*/  frames; } ;
struct iwl_mvm_reorder_buf_entry {TYPE_1__ e; } ;
struct iwl_mvm_baid_data {size_t tid; scalar_t__ sta_id; int entries_per_queue; struct iwl_mvm_reorder_buf_entry* entries; struct iwl_mvm_reorder_buffer* reorder_buf; } ;
struct iwl_mvm {int /*<<< orphan*/ * baid_map; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  device_timestamp; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_mvm*,char*,size_t,int) ; 
 int /*<<< orphan*/  IWL_MVM_RELEASE_SEND_RSS_SYNC ; 
 int IWL_RX_MPDU_AMSDU_LAST_SUBFRAME ; 
 size_t IWL_RX_MPDU_AMSDU_SUBFRAME_IDX_MASK ; 
 int IWL_RX_MPDU_MFLG2_AMSDU ; 
 int IWL_RX_MPDU_REORDER_BAID_MASK ; 
 int IWL_RX_MPDU_REORDER_BAID_SHIFT ; 
 int IWL_RX_MPDU_REORDER_BA_OLD_SN ; 
 int IWL_RX_MPDU_REORDER_NSSN_MASK ; 
 int IWL_RX_MPDU_REORDER_SN_MASK ; 
 int IWL_RX_MPDU_REORDER_SN_SHIFT ; 
 size_t IWL_RX_REORDER_DATA_INVALID_BAID ; 
 scalar_t__ WARN (int,char*,size_t,scalar_t__,size_t,scalar_t__,size_t) ; 
 scalar_t__ WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 size_t ieee80211_get_tid (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int ieee80211_sn_inc (int) ; 
 scalar_t__ ieee80211_sn_less (int,int) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_is_sn_less (int,int,int) ; 
 int /*<<< orphan*/  iwl_mvm_oldsn_workaround (struct iwl_mvm*,struct ieee80211_sta*,size_t,struct iwl_mvm_reorder_buffer*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_mvm_release_frames (struct iwl_mvm*,struct ieee80211_sta*,struct napi_struct*,struct iwl_mvm_baid_data*,struct iwl_mvm_reorder_buffer*,int,int /*<<< orphan*/ ) ; 
 struct ieee80211_hdr* iwl_mvm_skb_get_hdr (struct sk_buff*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_sync_nssn (struct iwl_mvm*,size_t,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_mvm_baid_data* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool iwl_mvm_reorder(struct iwl_mvm *mvm,
			    struct napi_struct *napi,
			    int queue,
			    struct ieee80211_sta *sta,
			    struct sk_buff *skb,
			    struct iwl_rx_mpdu_desc *desc)
{
	struct ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_hdr *hdr = iwl_mvm_skb_get_hdr(skb);
	struct iwl_mvm_sta *mvm_sta;
	struct iwl_mvm_baid_data *baid_data;
	struct iwl_mvm_reorder_buffer *buffer;
	struct sk_buff *tail;
	u32 reorder = le32_to_cpu(desc->reorder_data);
	bool amsdu = desc->mac_flags2 & IWL_RX_MPDU_MFLG2_AMSDU;
	bool last_subframe =
		desc->amsdu_info & IWL_RX_MPDU_AMSDU_LAST_SUBFRAME;
	u8 tid = ieee80211_get_tid(hdr);
	u8 sub_frame_idx = desc->amsdu_info &
			   IWL_RX_MPDU_AMSDU_SUBFRAME_IDX_MASK;
	struct iwl_mvm_reorder_buf_entry *entries;
	int index;
	u16 nssn, sn;
	u8 baid;

	baid = (reorder & IWL_RX_MPDU_REORDER_BAID_MASK) >>
		IWL_RX_MPDU_REORDER_BAID_SHIFT;

	/*
	 * This also covers the case of receiving a Block Ack Request
	 * outside a BA session; we'll pass it to mac80211 and that
	 * then sends a delBA action frame.
	 * This also covers pure monitor mode, in which case we won't
	 * have any BA sessions.
	 */
	if (baid == IWL_RX_REORDER_DATA_INVALID_BAID)
		return false;

	/* no sta yet */
	if (WARN_ONCE(IS_ERR_OR_NULL(sta),
		      "Got valid BAID without a valid station assigned\n"))
		return false;

	mvm_sta = iwl_mvm_sta_from_mac80211(sta);

	/* not a data packet or a bar */
	if (!ieee80211_is_back_req(hdr->frame_control) &&
	    (!ieee80211_is_data_qos(hdr->frame_control) ||
	     is_multicast_ether_addr(hdr->addr1)))
		return false;

	if (unlikely(!ieee80211_is_data_present(hdr->frame_control)))
		return false;

	baid_data = rcu_dereference(mvm->baid_map[baid]);
	if (!baid_data) {
		IWL_DEBUG_RX(mvm,
			     "Got valid BAID but no baid allocated, bypass the re-ordering buffer. Baid %d reorder 0x%x\n",
			      baid, reorder);
		return false;
	}

	if (WARN(tid != baid_data->tid || mvm_sta->sta_id != baid_data->sta_id,
		 "baid 0x%x is mapped to sta:%d tid:%d, but was received for sta:%d tid:%d\n",
		 baid, baid_data->sta_id, baid_data->tid, mvm_sta->sta_id,
		 tid))
		return false;

	nssn = reorder & IWL_RX_MPDU_REORDER_NSSN_MASK;
	sn = (reorder & IWL_RX_MPDU_REORDER_SN_MASK) >>
		IWL_RX_MPDU_REORDER_SN_SHIFT;

	buffer = &baid_data->reorder_buf[queue];
	entries = &baid_data->entries[queue * baid_data->entries_per_queue];

	spin_lock_bh(&buffer->lock);

	if (!buffer->valid) {
		if (reorder & IWL_RX_MPDU_REORDER_BA_OLD_SN) {
			spin_unlock_bh(&buffer->lock);
			return false;
		}
		buffer->valid = true;
	}

	if (ieee80211_is_back_req(hdr->frame_control)) {
		iwl_mvm_release_frames(mvm, sta, napi, baid_data,
				       buffer, nssn, 0);
		goto drop;
	}

	/*
	 * If there was a significant jump in the nssn - adjust.
	 * If the SN is smaller than the NSSN it might need to first go into
	 * the reorder buffer, in which case we just release up to it and the
	 * rest of the function will take care of storing it and releasing up to
	 * the nssn.
	 * This should not happen. This queue has been lagging and it should
	 * have been updated by a IWL_MVM_RXQ_NSSN_SYNC notification. Be nice
	 * and update the other queues.
	 */
	if (!iwl_mvm_is_sn_less(nssn, buffer->head_sn + buffer->buf_size,
				buffer->buf_size) ||
	    !ieee80211_sn_less(sn, buffer->head_sn + buffer->buf_size)) {
		u16 min_sn = ieee80211_sn_less(sn, nssn) ? sn : nssn;

		iwl_mvm_release_frames(mvm, sta, napi, baid_data, buffer,
				       min_sn, IWL_MVM_RELEASE_SEND_RSS_SYNC);
	}

	iwl_mvm_oldsn_workaround(mvm, sta, tid, buffer, reorder,
				 rx_status->device_timestamp, queue);

	/* drop any oudated packets */
	if (ieee80211_sn_less(sn, buffer->head_sn))
		goto drop;

	/* release immediately if allowed by nssn and no stored frames */
	if (!buffer->num_stored && ieee80211_sn_less(sn, nssn)) {
		if (iwl_mvm_is_sn_less(buffer->head_sn, nssn,
				       buffer->buf_size) &&
		   (!amsdu || last_subframe)) {
			/*
			 * If we crossed the 2048 or 0 SN, notify all the
			 * queues. This is done in order to avoid having a
			 * head_sn that lags behind for too long. When that
			 * happens, we can get to a situation where the head_sn
			 * is within the interval [nssn - buf_size : nssn]
			 * which will make us think that the nssn is a packet
			 * that we already freed because of the reordering
			 * buffer and we will ignore it. So maintain the
			 * head_sn somewhat updated across all the queues:
			 * when it crosses 0 and 2048.
			 */
			if (sn == 2048 || sn == 0)
				iwl_mvm_sync_nssn(mvm, baid, sn);
			buffer->head_sn = nssn;
		}
		/* No need to update AMSDU last SN - we are moving the head */
		spin_unlock_bh(&buffer->lock);
		return false;
	}

	/*
	 * release immediately if there are no stored frames, and the sn is
	 * equal to the head.
	 * This can happen due to reorder timer, where NSSN is behind head_sn.
	 * When we released everything, and we got the next frame in the
	 * sequence, according to the NSSN we can't release immediately,
	 * while technically there is no hole and we can move forward.
	 */
	if (!buffer->num_stored && sn == buffer->head_sn) {
		if (!amsdu || last_subframe) {
			if (sn == 2048 || sn == 0)
				iwl_mvm_sync_nssn(mvm, baid, sn);
			buffer->head_sn = ieee80211_sn_inc(buffer->head_sn);
		}
		/* No need to update AMSDU last SN - we are moving the head */
		spin_unlock_bh(&buffer->lock);
		return false;
	}

	index = sn % buffer->buf_size;

	/*
	 * Check if we already stored this frame
	 * As AMSDU is either received or not as whole, logic is simple:
	 * If we have frames in that position in the buffer and the last frame
	 * originated from AMSDU had a different SN then it is a retransmission.
	 * If it is the same SN then if the subframe index is incrementing it
	 * is the same AMSDU - otherwise it is a retransmission.
	 */
	tail = skb_peek_tail(&entries[index].e.frames);
	if (tail && !amsdu)
		goto drop;
	else if (tail && (sn != buffer->last_amsdu ||
			  buffer->last_sub_index >= sub_frame_idx))
		goto drop;

	/* put in reorder buffer */
	__skb_queue_tail(&entries[index].e.frames, skb);
	buffer->num_stored++;
	entries[index].e.reorder_time = jiffies;

	if (amsdu) {
		buffer->last_amsdu = sn;
		buffer->last_sub_index = sub_frame_idx;
	}

	/*
	 * We cannot trust NSSN for AMSDU sub-frames that are not the last.
	 * The reason is that NSSN advances on the first sub-frame, and may
	 * cause the reorder buffer to advance before all the sub-frames arrive.
	 * Example: reorder buffer contains SN 0 & 2, and we receive AMSDU with
	 * SN 1. NSSN for first sub frame will be 3 with the result of driver
	 * releasing SN 0,1, 2. When sub-frame 1 arrives - reorder buffer is
	 * already ahead and it will be dropped.
	 * If the last sub-frame is not on this queue - we will get frame
	 * release notification with up to date NSSN.
	 */
	if (!amsdu || last_subframe)
		iwl_mvm_release_frames(mvm, sta, napi, baid_data,
				       buffer, nssn,
				       IWL_MVM_RELEASE_SEND_RSS_SYNC);

	spin_unlock_bh(&buffer->lock);
	return true;

drop:
	kfree_skb(skb);
	spin_unlock_bh(&buffer->lock);
	return true;
}