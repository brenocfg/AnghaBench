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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct mwifiex_rx_reorder_tbl {int start_win; int win_size; struct sk_buff** rx_reorder_ptr; } ;
struct mwifiex_private {int /*<<< orphan*/  rx_reorder_tbl_lock; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mwifiex_11n_dispatch_pkt (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwifiex_11n_dispatch_pkt_until_start_win(struct mwifiex_private *priv,
					 struct mwifiex_rx_reorder_tbl *tbl,
					 int start_win)
{
	struct sk_buff_head list;
	struct sk_buff *skb;
	int pkt_to_send, i;

	__skb_queue_head_init(&list);
	spin_lock_bh(&priv->rx_reorder_tbl_lock);

	pkt_to_send = (start_win > tbl->start_win) ?
		      min((start_win - tbl->start_win), tbl->win_size) :
		      tbl->win_size;

	for (i = 0; i < pkt_to_send; ++i) {
		if (tbl->rx_reorder_ptr[i]) {
			skb = tbl->rx_reorder_ptr[i];
			__skb_queue_tail(&list, skb);
			tbl->rx_reorder_ptr[i] = NULL;
		}
	}

	/*
	 * We don't have a circular buffer, hence use rotation to simulate
	 * circular buffer
	 */
	for (i = 0; i < tbl->win_size - pkt_to_send; ++i) {
		tbl->rx_reorder_ptr[i] = tbl->rx_reorder_ptr[pkt_to_send + i];
		tbl->rx_reorder_ptr[pkt_to_send + i] = NULL;
	}

	tbl->start_win = start_win;
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	while ((skb = __skb_dequeue(&list)))
		mwifiex_11n_dispatch_pkt(priv, skb);
}