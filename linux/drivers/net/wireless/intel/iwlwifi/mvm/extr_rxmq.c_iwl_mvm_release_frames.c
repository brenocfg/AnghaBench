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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;
struct iwl_mvm_reorder_buffer {size_t queue; int head_sn; int buf_size; int /*<<< orphan*/  reorder_timer; int /*<<< orphan*/  removed; scalar_t__ num_stored; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ reorder_time; struct sk_buff_head frames; } ;
struct iwl_mvm_reorder_buf_entry {TYPE_1__ e; } ;
struct iwl_mvm_baid_data {size_t entries_per_queue; int /*<<< orphan*/  baid; struct iwl_mvm_reorder_buf_entry* entries; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int IWL_MVM_RELEASE_FROM_RSS_SYNC ; 
 int IWL_MVM_RELEASE_SEND_RSS_SYNC ; 
 scalar_t__ RX_REORDER_BUF_TIMEOUT_MQ ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int ieee80211_sn_inc (int) ; 
 scalar_t__ ieee80211_sn_less (int,int) ; 
 scalar_t__ iwl_mvm_is_sn_less (int,int,int) ; 
 int /*<<< orphan*/  iwl_mvm_pass_packet_to_mac80211 (struct iwl_mvm*,struct napi_struct*,struct sk_buff*,size_t,struct ieee80211_sta*,int) ; 
 int /*<<< orphan*/  iwl_mvm_sync_nssn (struct iwl_mvm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ skb_queue_empty (struct sk_buff_head*) ; 

__attribute__((used)) static void iwl_mvm_release_frames(struct iwl_mvm *mvm,
				   struct ieee80211_sta *sta,
				   struct napi_struct *napi,
				   struct iwl_mvm_baid_data *baid_data,
				   struct iwl_mvm_reorder_buffer *reorder_buf,
				   u16 nssn, u32 flags)
{
	struct iwl_mvm_reorder_buf_entry *entries =
		&baid_data->entries[reorder_buf->queue *
				    baid_data->entries_per_queue];
	u16 ssn = reorder_buf->head_sn;

	lockdep_assert_held(&reorder_buf->lock);

	/*
	 * We keep the NSSN not too far behind, if we are sync'ing it and it
	 * is more than 2048 ahead of us, it must be behind us. Discard it.
	 * This can happen if the queue that hit the 0 / 2048 seqno was lagging
	 * behind and this queue already processed packets. The next if
	 * would have caught cases where this queue would have processed less
	 * than 64 packets, but it may have processed more than 64 packets.
	 */
	if ((flags & IWL_MVM_RELEASE_FROM_RSS_SYNC) &&
	    ieee80211_sn_less(nssn, ssn))
		goto set_timer;

	/* ignore nssn smaller than head sn - this can happen due to timeout */
	if (iwl_mvm_is_sn_less(nssn, ssn, reorder_buf->buf_size))
		goto set_timer;

	while (iwl_mvm_is_sn_less(ssn, nssn, reorder_buf->buf_size)) {
		int index = ssn % reorder_buf->buf_size;
		struct sk_buff_head *skb_list = &entries[index].e.frames;
		struct sk_buff *skb;

		ssn = ieee80211_sn_inc(ssn);
		if ((flags & IWL_MVM_RELEASE_SEND_RSS_SYNC) &&
		    (ssn == 2048 || ssn == 0))
			iwl_mvm_sync_nssn(mvm, baid_data->baid, ssn);

		/*
		 * Empty the list. Will have more than one frame for A-MSDU.
		 * Empty list is valid as well since nssn indicates frames were
		 * received.
		 */
		while ((skb = __skb_dequeue(skb_list))) {
			iwl_mvm_pass_packet_to_mac80211(mvm, napi, skb,
							reorder_buf->queue,
							sta, false);
			reorder_buf->num_stored--;
		}
	}
	reorder_buf->head_sn = nssn;

set_timer:
	if (reorder_buf->num_stored && !reorder_buf->removed) {
		u16 index = reorder_buf->head_sn % reorder_buf->buf_size;

		while (skb_queue_empty(&entries[index].e.frames))
			index = (index + 1) % reorder_buf->buf_size;
		/* modify timer to match next frame's expiration time */
		mod_timer(&reorder_buf->reorder_timer,
			  entries[index].e.reorder_time + 1 +
			  RX_REORDER_BUF_TIMEOUT_MQ);
	} else {
		del_timer(&reorder_buf->reorder_timer);
	}
}