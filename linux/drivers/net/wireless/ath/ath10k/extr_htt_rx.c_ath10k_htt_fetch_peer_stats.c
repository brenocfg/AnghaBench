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
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_sta {int dummy; } ;
struct htt_resp_hdr {int dummy; } ;
struct TYPE_2__ {int num_ppdu; int ppdu_len; scalar_t__ payload; } ;
struct htt_resp {TYPE_1__ peer_tx_stats; } ;
struct htt_per_peer_tx_stats_ind {int /*<<< orphan*/  tx_duration; int /*<<< orphan*/  failed_pkts; int /*<<< orphan*/  retry_pkts; int /*<<< orphan*/  succ_pkts; int /*<<< orphan*/  flags; int /*<<< orphan*/  ratecode; int /*<<< orphan*/  failed_bytes; int /*<<< orphan*/  retry_bytes; int /*<<< orphan*/  succ_bytes; int /*<<< orphan*/  peer_id; } ;
struct ath10k_per_peer_tx_stats {void* duration; void* failed_pkts; void* retry_pkts; void* succ_pkts; int /*<<< orphan*/  flags; int /*<<< orphan*/  ratecode; void* failed_bytes; void* retry_bytes; void* succ_bytes; } ;
struct ath10k_peer {struct ieee80211_sta* sta; } ;
struct ath10k {int /*<<< orphan*/  data_lock; struct ath10k_per_peer_tx_stats peer_tx_stats; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ath10k_peer* ath10k_peer_find_by_id (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_update_per_peer_tx_stats (struct ath10k*,struct ieee80211_sta*,struct ath10k_per_peer_tx_stats*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_htt_fetch_peer_stats(struct ath10k *ar,
					struct sk_buff *skb)
{
	struct htt_resp *resp = (struct htt_resp *)skb->data;
	struct ath10k_per_peer_tx_stats *p_tx_stats = &ar->peer_tx_stats;
	struct htt_per_peer_tx_stats_ind *tx_stats;
	struct ieee80211_sta *sta;
	struct ath10k_peer *peer;
	int peer_id, i;
	u8 ppdu_len, num_ppdu;

	num_ppdu = resp->peer_tx_stats.num_ppdu;
	ppdu_len = resp->peer_tx_stats.ppdu_len * sizeof(__le32);

	if (skb->len < sizeof(struct htt_resp_hdr) + num_ppdu * ppdu_len) {
		ath10k_warn(ar, "Invalid peer stats buf length %d\n", skb->len);
		return;
	}

	tx_stats = (struct htt_per_peer_tx_stats_ind *)
			(resp->peer_tx_stats.payload);
	peer_id = __le16_to_cpu(tx_stats->peer_id);

	rcu_read_lock();
	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, peer_id);
	if (!peer || !peer->sta) {
		ath10k_warn(ar, "Invalid peer id %d peer stats buffer\n",
			    peer_id);
		goto out;
	}

	sta = peer->sta;
	for (i = 0; i < num_ppdu; i++) {
		tx_stats = (struct htt_per_peer_tx_stats_ind *)
			   (resp->peer_tx_stats.payload + i * ppdu_len);

		p_tx_stats->succ_bytes = __le32_to_cpu(tx_stats->succ_bytes);
		p_tx_stats->retry_bytes = __le32_to_cpu(tx_stats->retry_bytes);
		p_tx_stats->failed_bytes =
				__le32_to_cpu(tx_stats->failed_bytes);
		p_tx_stats->ratecode = tx_stats->ratecode;
		p_tx_stats->flags = tx_stats->flags;
		p_tx_stats->succ_pkts = __le16_to_cpu(tx_stats->succ_pkts);
		p_tx_stats->retry_pkts = __le16_to_cpu(tx_stats->retry_pkts);
		p_tx_stats->failed_pkts = __le16_to_cpu(tx_stats->failed_pkts);
		p_tx_stats->duration = __le16_to_cpu(tx_stats->tx_duration);

		ath10k_update_per_peer_tx_stats(ar, sta, p_tx_stats);
	}

out:
	spin_unlock_bh(&ar->data_lock);
	rcu_read_unlock();
}