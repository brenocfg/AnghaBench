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
struct wcn36xx_vif {int dummy; } ;
struct wcn36xx_tx_bd {int tx_comp; int tx_bd_sign; int /*<<< orphan*/  dpu_rf; } ;
struct wcn36xx_sta {int dummy; } ;
struct wcn36xx {int /*<<< orphan*/  hw; int /*<<< orphan*/  dxe_lock; struct sk_buff* tx_ack_skb; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr1; } ;
typedef  int /*<<< orphan*/  bd ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_SEQ_TO_SN (int /*<<< orphan*/ ) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int /*<<< orphan*/  WCN36XX_BMU_WQ_TX ; 
 int /*<<< orphan*/  WCN36XX_DBG_DXE ; 
 int /*<<< orphan*/  WCN36XX_DBG_TX ; 
 int /*<<< orphan*/  WCN36XX_DBG_TX_DUMP ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buff_to_be (int /*<<< orphan*/ *,int) ; 
 int ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wcn36xx_tx_bd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wcn36xx_dbg_dump (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int wcn36xx_dxe_tx_frame (struct wcn36xx*,struct wcn36xx_vif*,struct wcn36xx_tx_bd*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  wcn36xx_set_tx_data (struct wcn36xx_tx_bd*,struct wcn36xx*,struct wcn36xx_vif**,struct wcn36xx_sta*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  wcn36xx_set_tx_mgmt (struct wcn36xx_tx_bd*,struct wcn36xx*,struct wcn36xx_vif**,struct sk_buff*,int) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*) ; 

int wcn36xx_start_tx(struct wcn36xx *wcn,
		     struct wcn36xx_sta *sta_priv,
		     struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct wcn36xx_vif *vif_priv = NULL;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	unsigned long flags;
	bool is_low = ieee80211_is_data(hdr->frame_control);
	bool bcast = is_broadcast_ether_addr(hdr->addr1) ||
		is_multicast_ether_addr(hdr->addr1);
	struct wcn36xx_tx_bd bd;
	int ret;

	memset(&bd, 0, sizeof(bd));

	wcn36xx_dbg(WCN36XX_DBG_TX,
		    "tx skb %p len %d fc %04x sn %d %s %s\n",
		    skb, skb->len, __le16_to_cpu(hdr->frame_control),
		    IEEE80211_SEQ_TO_SN(__le16_to_cpu(hdr->seq_ctrl)),
		    is_low ? "low" : "high", bcast ? "bcast" : "ucast");

	wcn36xx_dbg_dump(WCN36XX_DBG_TX_DUMP, "", skb->data, skb->len);

	bd.dpu_rf = WCN36XX_BMU_WQ_TX;

	bd.tx_comp = !!(info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS);
	if (bd.tx_comp) {
		wcn36xx_dbg(WCN36XX_DBG_DXE, "TX_ACK status requested\n");
		spin_lock_irqsave(&wcn->dxe_lock, flags);
		if (wcn->tx_ack_skb) {
			spin_unlock_irqrestore(&wcn->dxe_lock, flags);
			wcn36xx_warn("tx_ack_skb already set\n");
			return -EINVAL;
		}

		wcn->tx_ack_skb = skb;
		spin_unlock_irqrestore(&wcn->dxe_lock, flags);

		/* Only one at a time is supported by fw. Stop the TX queues
		 * until the ack status gets back.
		 *
		 * TODO: Add watchdog in case FW does not answer
		 */
		ieee80211_stop_queues(wcn->hw);
	}

	/* Data frames served first*/
	if (is_low)
		wcn36xx_set_tx_data(&bd, wcn, &vif_priv, sta_priv, skb, bcast);
	else
		/* MGMT and CTRL frames are handeld here*/
		wcn36xx_set_tx_mgmt(&bd, wcn, &vif_priv, skb, bcast);

	buff_to_be((u32 *)&bd, sizeof(bd)/sizeof(u32));
	bd.tx_bd_sign = 0xbdbdbdbd;

	ret = wcn36xx_dxe_tx_frame(wcn, vif_priv, &bd, skb, is_low);
	if (ret && bd.tx_comp) {
		/* If the skb has not been transmitted,
		 * don't keep a reference to it.
		 */
		spin_lock_irqsave(&wcn->dxe_lock, flags);
		wcn->tx_ack_skb = NULL;
		spin_unlock_irqrestore(&wcn->dxe_lock, flags);

		ieee80211_wake_queues(wcn->hw);
	}

	return ret;
}