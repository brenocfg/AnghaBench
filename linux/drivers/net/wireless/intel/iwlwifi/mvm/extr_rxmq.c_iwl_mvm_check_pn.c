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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct iwl_mvm_sta {int /*<<< orphan*/ * ptk_pn; } ;
struct iwl_mvm_key_pn {TYPE_1__* q; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr1; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pn; } ;

/* Variables and functions */
 int IEEE80211_CCMP_PN_LEN ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int IWL_MAX_TID_COUNT ; 
 int RX_FLAG_ALLOW_SAME_PN ; 
 int RX_FLAG_DECRYPTED ; 
 int RX_FLAG_PN_VALIDATED ; 
 int ieee80211_get_tid (struct ieee80211_hdr*) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 struct ieee80211_hdr* iwl_mvm_skb_get_hdr (struct sk_buff*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct iwl_mvm_key_pn* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int iwl_mvm_check_pn(struct iwl_mvm *mvm, struct sk_buff *skb,
				   int queue, struct ieee80211_sta *sta)
{
	struct iwl_mvm_sta *mvmsta;
	struct ieee80211_hdr *hdr = iwl_mvm_skb_get_hdr(skb);
	struct ieee80211_rx_status *stats = IEEE80211_SKB_RXCB(skb);
	struct iwl_mvm_key_pn *ptk_pn;
	int res;
	u8 tid, keyidx;
	u8 pn[IEEE80211_CCMP_PN_LEN];
	u8 *extiv;

	/* do PN checking */

	/* multicast and non-data only arrives on default queue */
	if (!ieee80211_is_data(hdr->frame_control) ||
	    is_multicast_ether_addr(hdr->addr1))
		return 0;

	/* do not check PN for open AP */
	if (!(stats->flag & RX_FLAG_DECRYPTED))
		return 0;

	/*
	 * avoid checking for default queue - we don't want to replicate
	 * all the logic that's necessary for checking the PN on fragmented
	 * frames, leave that to mac80211
	 */
	if (queue == 0)
		return 0;

	/* if we are here - this for sure is either CCMP or GCMP */
	if (IS_ERR_OR_NULL(sta)) {
		IWL_ERR(mvm,
			"expected hw-decrypted unicast frame for station\n");
		return -1;
	}

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	extiv = (u8 *)hdr + ieee80211_hdrlen(hdr->frame_control);
	keyidx = extiv[3] >> 6;

	ptk_pn = rcu_dereference(mvmsta->ptk_pn[keyidx]);
	if (!ptk_pn)
		return -1;

	if (ieee80211_is_data_qos(hdr->frame_control))
		tid = ieee80211_get_tid(hdr);
	else
		tid = 0;

	/* we don't use HCCA/802.11 QoS TSPECs, so drop such frames */
	if (tid >= IWL_MAX_TID_COUNT)
		return -1;

	/* load pn */
	pn[0] = extiv[7];
	pn[1] = extiv[6];
	pn[2] = extiv[5];
	pn[3] = extiv[4];
	pn[4] = extiv[1];
	pn[5] = extiv[0];

	res = memcmp(pn, ptk_pn->q[queue].pn[tid], IEEE80211_CCMP_PN_LEN);
	if (res < 0)
		return -1;
	if (!res && !(stats->flag & RX_FLAG_ALLOW_SAME_PN))
		return -1;

	memcpy(ptk_pn->q[queue].pn[tid], pn, IEEE80211_CCMP_PN_LEN);
	stats->flag |= RX_FLAG_PN_VALIDATED;

	return 0;
}