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
struct sk_buff_head {int dummy; } ;
struct sk_buff {unsigned int data_len; int /*<<< orphan*/  cb; } ;
struct iwl_mvm_sta {scalar_t__ sta_id; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_tx_info {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_2__ {unsigned int gso_size; } ;

/* Variables and functions */
 scalar_t__ IWL_MVM_INVALID_STA ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int iwl_mvm_tx_mpdu (struct iwl_mvm*,struct sk_buff*,struct ieee80211_tx_info*,struct ieee80211_sta*) ; 
 int iwl_mvm_tx_tso (struct iwl_mvm*,struct sk_buff*,struct ieee80211_tx_info*,struct ieee80211_sta*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_tx_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_tail_pointer (struct sk_buff*) ; 
 unsigned int skb_transport_header (struct sk_buff*) ; 
 unsigned int tcp_hdrlen (struct sk_buff*) ; 

int iwl_mvm_tx_skb(struct iwl_mvm *mvm, struct sk_buff *skb,
		   struct ieee80211_sta *sta)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	struct ieee80211_tx_info info;
	struct sk_buff_head mpdus_skbs;
	unsigned int payload_len;
	int ret;

	if (WARN_ON_ONCE(!mvmsta))
		return -1;

	if (WARN_ON_ONCE(mvmsta->sta_id == IWL_MVM_INVALID_STA))
		return -1;

	memcpy(&info, skb->cb, sizeof(info));

	if (!skb_is_gso(skb))
		return iwl_mvm_tx_mpdu(mvm, skb, &info, sta);

	payload_len = skb_tail_pointer(skb) - skb_transport_header(skb) -
		tcp_hdrlen(skb) + skb->data_len;

	if (payload_len <= skb_shinfo(skb)->gso_size)
		return iwl_mvm_tx_mpdu(mvm, skb, &info, sta);

	__skb_queue_head_init(&mpdus_skbs);

	ret = iwl_mvm_tx_tso(mvm, skb, &info, sta, &mpdus_skbs);
	if (ret)
		return ret;

	if (WARN_ON(skb_queue_empty(&mpdus_skbs)))
		return ret;

	while (!skb_queue_empty(&mpdus_skbs)) {
		skb = __skb_dequeue(&mpdus_skbs);

		ret = iwl_mvm_tx_mpdu(mvm, skb, &info, sta);
		if (ret) {
			__skb_queue_purge(&mpdus_skbs);
			return ret;
		}
	}

	return 0;
}