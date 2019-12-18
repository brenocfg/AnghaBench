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
struct mwifiex_rx_reorder_tbl {int win_size; int start_win; struct sk_buff** rx_reorder_ptr; } ;
struct mwifiex_private {int /*<<< orphan*/  rx_reorder_tbl_lock; } ;

/* Variables and functions */
 int MAX_TID_VALUE ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  mwifiex_11n_dispatch_pkt (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwifiex_11n_scan_and_dispatch(struct mwifiex_private *priv,
			      struct mwifiex_rx_reorder_tbl *tbl)
{
	struct sk_buff_head list;
	struct sk_buff *skb;
	int i, j, xchg;

	__skb_queue_head_init(&list);
	spin_lock_bh(&priv->rx_reorder_tbl_lock);

	for (i = 0; i < tbl->win_size; ++i) {
		if (!tbl->rx_reorder_ptr[i])
			break;
		skb = tbl->rx_reorder_ptr[i];
		__skb_queue_tail(&list, skb);
		tbl->rx_reorder_ptr[i] = NULL;
	}

	/*
	 * We don't have a circular buffer, hence use rotation to simulate
	 * circular buffer
	 */
	if (i > 0) {
		xchg = tbl->win_size - i;
		for (j = 0; j < xchg; ++j) {
			tbl->rx_reorder_ptr[j] = tbl->rx_reorder_ptr[i + j];
			tbl->rx_reorder_ptr[i + j] = NULL;
		}
	}
	tbl->start_win = (tbl->start_win + i) & (MAX_TID_VALUE - 1);

	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	while ((skb = __skb_dequeue(&list)))
		mwifiex_11n_dispatch_pkt(priv, skb);
}