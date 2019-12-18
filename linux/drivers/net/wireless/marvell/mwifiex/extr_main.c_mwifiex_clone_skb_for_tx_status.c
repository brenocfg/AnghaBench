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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct mwifiex_txinfo {int ack_frame_id; int /*<<< orphan*/  cookie; int /*<<< orphan*/  flags; } ;
struct mwifiex_private {int /*<<< orphan*/  ack_status_lock; int /*<<< orphan*/  ack_status_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MWIFIEX_BUF_FLAG_ACTION_TX_STATUS ; 
 struct mwifiex_txinfo* MWIFIEX_SKB_TXCB (struct sk_buff*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct sk_buff *
mwifiex_clone_skb_for_tx_status(struct mwifiex_private *priv,
				struct sk_buff *skb, u8 flag, u64 *cookie)
{
	struct sk_buff *orig_skb = skb;
	struct mwifiex_txinfo *tx_info, *orig_tx_info;

	skb = skb_clone(skb, GFP_ATOMIC);
	if (skb) {
		int id;

		spin_lock_bh(&priv->ack_status_lock);
		id = idr_alloc(&priv->ack_status_frames, orig_skb,
			       1, 0x10, GFP_ATOMIC);
		spin_unlock_bh(&priv->ack_status_lock);

		if (id >= 0) {
			tx_info = MWIFIEX_SKB_TXCB(skb);
			tx_info->ack_frame_id = id;
			tx_info->flags |= flag;
			orig_tx_info = MWIFIEX_SKB_TXCB(orig_skb);
			orig_tx_info->ack_frame_id = id;
			orig_tx_info->flags |= flag;

			if (flag == MWIFIEX_BUF_FLAG_ACTION_TX_STATUS && cookie)
				orig_tx_info->cookie = *cookie;

		} else if (skb_shared(skb)) {
			kfree_skb(orig_skb);
		} else {
			kfree_skb(skb);
			skb = orig_skb;
		}
	} else {
		/* couldn't clone -- lose tx status ... */
		skb = orig_skb;
	}

	return skb;
}