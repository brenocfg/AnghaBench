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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct mgmt_tx_compl_params {int /*<<< orphan*/  desc_id; scalar_t__ ack_rssi; scalar_t__ status; } ;
struct TYPE_2__ {int is_valid_ack_signal; scalar_t__ ack_signal; } ;
struct ieee80211_tx_info {TYPE_1__ status; int /*<<< orphan*/  flags; } ;
struct ath10k_wmi {int /*<<< orphan*/  mgmt_pending_tx; } ;
struct ath10k_mgmt_tx_pkt_addr {int /*<<< orphan*/  paddr; struct sk_buff* vaddr; } ;
struct ath10k {int /*<<< orphan*/  data_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  dev; struct ath10k_wmi wmi; } ;

/* Variables and functions */
 scalar_t__ ATH10K_DEFAULT_NOISE_FLOOR ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOENT ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath10k_mgmt_tx_pkt_addr* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wmi_process_mgmt_tx_comp(struct ath10k *ar, struct mgmt_tx_compl_params *param)
{
	struct ath10k_mgmt_tx_pkt_addr *pkt_addr;
	struct ath10k_wmi *wmi = &ar->wmi;
	struct ieee80211_tx_info *info;
	struct sk_buff *msdu;
	int ret;

	spin_lock_bh(&ar->data_lock);

	pkt_addr = idr_find(&wmi->mgmt_pending_tx, param->desc_id);
	if (!pkt_addr) {
		ath10k_warn(ar, "received mgmt tx completion for invalid msdu_id: %d\n",
			    param->desc_id);
		ret = -ENOENT;
		goto out;
	}

	msdu = pkt_addr->vaddr;
	dma_unmap_single(ar->dev, pkt_addr->paddr,
			 msdu->len, DMA_TO_DEVICE);
	info = IEEE80211_SKB_CB(msdu);

	if (param->status) {
		info->flags &= ~IEEE80211_TX_STAT_ACK;
	} else {
		info->flags |= IEEE80211_TX_STAT_ACK;
		info->status.ack_signal = ATH10K_DEFAULT_NOISE_FLOOR +
					  param->ack_rssi;
		info->status.is_valid_ack_signal = true;
	}

	ieee80211_tx_status_irqsafe(ar->hw, msdu);

	ret = 0;

out:
	idr_remove(&wmi->mgmt_pending_tx, param->desc_id);
	spin_unlock_bh(&ar->data_lock);
	return ret;
}