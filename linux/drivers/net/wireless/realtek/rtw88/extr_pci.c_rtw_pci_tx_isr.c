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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int rp; int len; int /*<<< orphan*/  wp; } ;
struct rtw_pci_tx_ring {int queue_stopped; TYPE_2__ r; int /*<<< orphan*/  queue; } ;
struct rtw_pci_tx_data {int /*<<< orphan*/  sn; int /*<<< orphan*/  dma; } ;
struct rtw_pci {int /*<<< orphan*/  pdev; struct rtw_pci_tx_ring* tx_rings; } ;
struct rtw_dev {TYPE_1__* chip; struct ieee80211_hw* hw; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_pkt_desc_sz; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int IEEE80211_TX_STAT_ACK ; 
 int IEEE80211_TX_STAT_NOACK_TRANSMITTED ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 size_t RTW_TX_QUEUE_H2C ; 
 int avail_desc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtw_pci_tx_data* rtw_pci_get_tx_data (struct sk_buff*) ; 
 int* rtw_pci_tx_queue_idx_addr ; 
 int rtw_read32 (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_tx_report_enqueue (struct rtw_dev*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_pci_tx_isr(struct rtw_dev *rtwdev, struct rtw_pci *rtwpci,
			   u8 hw_queue)
{
	struct ieee80211_hw *hw = rtwdev->hw;
	struct ieee80211_tx_info *info;
	struct rtw_pci_tx_ring *ring;
	struct rtw_pci_tx_data *tx_data;
	struct sk_buff *skb;
	u32 count;
	u32 bd_idx_addr;
	u32 bd_idx, cur_rp;
	u16 q_map;

	ring = &rtwpci->tx_rings[hw_queue];

	bd_idx_addr = rtw_pci_tx_queue_idx_addr[hw_queue];
	bd_idx = rtw_read32(rtwdev, bd_idx_addr);
	cur_rp = bd_idx >> 16;
	cur_rp &= 0xfff;
	if (cur_rp >= ring->r.rp)
		count = cur_rp - ring->r.rp;
	else
		count = ring->r.len - (ring->r.rp - cur_rp);

	while (count--) {
		skb = skb_dequeue(&ring->queue);
		tx_data = rtw_pci_get_tx_data(skb);
		pci_unmap_single(rtwpci->pdev, tx_data->dma, skb->len,
				 PCI_DMA_TODEVICE);

		/* just free command packets from host to card */
		if (hw_queue == RTW_TX_QUEUE_H2C) {
			dev_kfree_skb_irq(skb);
			continue;
		}

		if (ring->queue_stopped &&
		    avail_desc(ring->r.wp, ring->r.rp, ring->r.len) > 4) {
			q_map = skb_get_queue_mapping(skb);
			ieee80211_wake_queue(hw, q_map);
			ring->queue_stopped = false;
		}

		skb_pull(skb, rtwdev->chip->tx_pkt_desc_sz);

		info = IEEE80211_SKB_CB(skb);

		/* enqueue to wait for tx report */
		if (info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS) {
			rtw_tx_report_enqueue(rtwdev, skb, tx_data->sn);
			continue;
		}

		/* always ACK for others, then they won't be marked as drop */
		if (info->flags & IEEE80211_TX_CTL_NO_ACK)
			info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;
		else
			info->flags |= IEEE80211_TX_STAT_ACK;

		ieee80211_tx_info_clear_status(info);
		ieee80211_tx_status_irqsafe(hw, skb);
	}

	ring->r.rp = cur_rp;
}