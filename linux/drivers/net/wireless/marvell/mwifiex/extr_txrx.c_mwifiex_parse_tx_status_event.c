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
typedef  int /*<<< orphan*/  u16 ;
struct tx_status_event {int /*<<< orphan*/  status; int /*<<< orphan*/  tx_token_id; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct mwifiex_txinfo {int flags; int /*<<< orphan*/  cookie; } ;
struct mwifiex_private {int /*<<< orphan*/  wdev; int /*<<< orphan*/  ack_status_lock; int /*<<< orphan*/  ack_status_frames; TYPE_1__* adapter; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct TYPE_2__ {scalar_t__ event_body; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MWIFIEX_BUF_FLAG_EAPOL_TX_STATUS ; 
 scalar_t__ MWIFIEX_MGMT_FRAME_HEADER_SIZE ; 
 struct mwifiex_txinfo* MWIFIEX_SKB_TXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  cfg80211_mgmt_tx_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_complete_wifi_ack (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mwifiex_parse_tx_status_event(struct mwifiex_private *priv,
				   void *event_body)
{
	struct tx_status_event *tx_status = (void *)priv->adapter->event_body;
	struct sk_buff *ack_skb;
	struct mwifiex_txinfo *tx_info;

	if (!tx_status->tx_token_id)
		return;

	spin_lock_bh(&priv->ack_status_lock);
	ack_skb = idr_remove(&priv->ack_status_frames, tx_status->tx_token_id);
	spin_unlock_bh(&priv->ack_status_lock);

	if (ack_skb) {
		tx_info = MWIFIEX_SKB_TXCB(ack_skb);

		if (tx_info->flags & MWIFIEX_BUF_FLAG_EAPOL_TX_STATUS) {
			/* consumes ack_skb */
			skb_complete_wifi_ack(ack_skb, !tx_status->status);
		} else {
			/* Remove broadcast address which was added by driver */
			memmove(ack_skb->data +
				sizeof(struct ieee80211_hdr_3addr) +
				MWIFIEX_MGMT_FRAME_HEADER_SIZE + sizeof(u16),
				ack_skb->data +
				sizeof(struct ieee80211_hdr_3addr) +
				MWIFIEX_MGMT_FRAME_HEADER_SIZE + sizeof(u16) +
				ETH_ALEN, ack_skb->len -
				(sizeof(struct ieee80211_hdr_3addr) +
				MWIFIEX_MGMT_FRAME_HEADER_SIZE + sizeof(u16) +
				ETH_ALEN));
			ack_skb->len = ack_skb->len - ETH_ALEN;
			/* Remove driver's proprietary header including 2 bytes
			 * of packet length and pass actual management frame buffer
			 * to cfg80211.
			 */
			cfg80211_mgmt_tx_status(&priv->wdev, tx_info->cookie,
						ack_skb->data +
						MWIFIEX_MGMT_FRAME_HEADER_SIZE +
						sizeof(u16), ack_skb->len -
						(MWIFIEX_MGMT_FRAME_HEADER_SIZE
						 + sizeof(u16)),
						!tx_status->status, GFP_ATOMIC);
			dev_kfree_skb_any(ack_skb);
		}
	}
}