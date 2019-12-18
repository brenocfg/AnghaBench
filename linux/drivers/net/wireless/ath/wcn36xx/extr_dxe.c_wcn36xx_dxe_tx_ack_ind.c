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
typedef  int u32 ;
struct wcn36xx {int /*<<< orphan*/  hw; int /*<<< orphan*/  dxe_lock; struct sk_buff* tx_ack_skb; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  WCN36XX_DBG_DXE ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*) ; 

void wcn36xx_dxe_tx_ack_ind(struct wcn36xx *wcn, u32 status)
{
	struct ieee80211_tx_info *info;
	struct sk_buff *skb;
	unsigned long flags;

	spin_lock_irqsave(&wcn->dxe_lock, flags);
	skb = wcn->tx_ack_skb;
	wcn->tx_ack_skb = NULL;
	spin_unlock_irqrestore(&wcn->dxe_lock, flags);

	if (!skb) {
		wcn36xx_warn("Spurious TX complete indication\n");
		return;
	}

	info = IEEE80211_SKB_CB(skb);

	if (status == 1)
		info->flags |= IEEE80211_TX_STAT_ACK;

	wcn36xx_dbg(WCN36XX_DBG_DXE, "dxe tx ack status: %d\n", status);

	ieee80211_tx_status_irqsafe(wcn->hw, skb);
	ieee80211_wake_queues(wcn->hw);
}