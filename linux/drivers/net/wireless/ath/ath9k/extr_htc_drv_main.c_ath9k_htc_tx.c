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
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMIT ; 
 int /*<<< orphan*/  ath9k_htc_check_stop_queues (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_tx_clear_slot (struct ath9k_htc_priv*,int) ; 
 int ath9k_htc_tx_get_slot (struct ath9k_htc_priv*) ; 
 int ath9k_htc_tx_start (struct ath9k_htc_priv*,int /*<<< orphan*/ ,struct sk_buff*,int,int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void ath9k_htc_tx(struct ieee80211_hw *hw,
			 struct ieee80211_tx_control *control,
			 struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr;
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath_common *common = ath9k_hw_common(priv->ah);
	int padpos, padsize, ret, slot;

	hdr = (struct ieee80211_hdr *) skb->data;

	/* Add the padding after the header if this is not already done */
	padpos = ieee80211_hdrlen(hdr->frame_control);
	padsize = padpos & 3;
	if (padsize && skb->len > padpos) {
		if (skb_headroom(skb) < padsize) {
			ath_dbg(common, XMIT, "No room for padding\n");
			goto fail_tx;
		}
		skb_push(skb, padsize);
		memmove(skb->data, skb->data + padsize, padpos);
	}

	slot = ath9k_htc_tx_get_slot(priv);
	if (slot < 0) {
		ath_dbg(common, XMIT, "No free TX slot\n");
		goto fail_tx;
	}

	ret = ath9k_htc_tx_start(priv, control->sta, skb, slot, false);
	if (ret != 0) {
		ath_dbg(common, XMIT, "Tx failed\n");
		goto clear_slot;
	}

	ath9k_htc_check_stop_queues(priv);

	return;

clear_slot:
	ath9k_htc_tx_clear_slot(priv, slot);
fail_tx:
	dev_kfree_skb_any(skb);
}