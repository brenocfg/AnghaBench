#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_rx_status {int /*<<< orphan*/  freq; int /*<<< orphan*/  band; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; int /*<<< orphan*/  band; } ;
struct htt_rx_desc {int dummy; } ;
struct ath10k {int /*<<< orphan*/  data_lock; struct ieee80211_channel* tgt_oper_chan; struct ieee80211_channel* rx_channel; struct ieee80211_channel* scan_channel; } ;

/* Variables and functions */
 struct ieee80211_channel* ath10k_htt_rx_h_any_channel (struct ath10k*) ; 
 struct ieee80211_channel* ath10k_htt_rx_h_peer_channel (struct ath10k*,struct htt_rx_desc*) ; 
 struct ieee80211_channel* ath10k_htt_rx_h_vdev_channel (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath10k_htt_rx_h_channel(struct ath10k *ar,
				    struct ieee80211_rx_status *status,
				    struct htt_rx_desc *rxd,
				    u32 vdev_id)
{
	struct ieee80211_channel *ch;

	spin_lock_bh(&ar->data_lock);
	ch = ar->scan_channel;
	if (!ch)
		ch = ar->rx_channel;
	if (!ch)
		ch = ath10k_htt_rx_h_peer_channel(ar, rxd);
	if (!ch)
		ch = ath10k_htt_rx_h_vdev_channel(ar, vdev_id);
	if (!ch)
		ch = ath10k_htt_rx_h_any_channel(ar);
	if (!ch)
		ch = ar->tgt_oper_chan;
	spin_unlock_bh(&ar->data_lock);

	if (!ch)
		return false;

	status->band = ch->band;
	status->freq = ch->center_freq;

	return true;
}