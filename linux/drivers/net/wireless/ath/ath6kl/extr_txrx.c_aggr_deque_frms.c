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
typedef  size_t u8 ;
typedef  size_t u16 ;
struct skb_hold_q {int /*<<< orphan*/ * skb; scalar_t__ is_amsdu; } ;
struct sk_buff {int dummy; } ;
struct rxtid_stats {int /*<<< orphan*/  num_delivered; int /*<<< orphan*/  num_hole; } ;
struct rxtid {size_t seq_next; int /*<<< orphan*/  q; int /*<<< orphan*/  lock; int /*<<< orphan*/  hold_q_sz; struct skb_hold_q* hold_q; } ;
struct aggr_info_conn {int /*<<< orphan*/  dev; int /*<<< orphan*/  aggr_info; struct rxtid_stats* stat; struct rxtid* rx_tid; } ;

/* Variables and functions */
 size_t AGGR_WIN_IDX (size_t,int /*<<< orphan*/ ) ; 
 size_t ATH6KL_NEXT_SEQ_NO (size_t) ; 
 int /*<<< orphan*/  aggr_slice_amsdu (int /*<<< orphan*/ ,struct rxtid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath6kl_deliver_frames_to_nw_stack (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aggr_deque_frms(struct aggr_info_conn *agg_conn, u8 tid,
			    u16 seq_no, u8 order)
{
	struct sk_buff *skb;
	struct rxtid *rxtid;
	struct skb_hold_q *node;
	u16 idx, idx_end, seq_end;
	struct rxtid_stats *stats;

	rxtid = &agg_conn->rx_tid[tid];
	stats = &agg_conn->stat[tid];

	spin_lock_bh(&rxtid->lock);
	idx = AGGR_WIN_IDX(rxtid->seq_next, rxtid->hold_q_sz);

	/*
	 * idx_end is typically the last possible frame in the window,
	 * but changes to 'the' seq_no, when BAR comes. If seq_no
	 * is non-zero, we will go up to that and stop.
	 * Note: last seq no in current window will occupy the same
	 * index position as index that is just previous to start.
	 * An imp point : if win_sz is 7, for seq_no space of 4095,
	 * then, there would be holes when sequence wrap around occurs.
	 * Target should judiciously choose the win_sz, based on
	 * this condition. For 4095, (TID_WINDOW_SZ = 2 x win_sz
	 * 2, 4, 8, 16 win_sz works fine).
	 * We must deque from "idx" to "idx_end", including both.
	 */
	seq_end = seq_no ? seq_no : rxtid->seq_next;
	idx_end = AGGR_WIN_IDX(seq_end, rxtid->hold_q_sz);

	do {
		node = &rxtid->hold_q[idx];
		if ((order == 1) && (!node->skb))
			break;

		if (node->skb) {
			if (node->is_amsdu)
				aggr_slice_amsdu(agg_conn->aggr_info, rxtid,
						 node->skb);
			else
				skb_queue_tail(&rxtid->q, node->skb);
			node->skb = NULL;
		} else {
			stats->num_hole++;
		}

		rxtid->seq_next = ATH6KL_NEXT_SEQ_NO(rxtid->seq_next);
		idx = AGGR_WIN_IDX(rxtid->seq_next, rxtid->hold_q_sz);
	} while (idx != idx_end);

	spin_unlock_bh(&rxtid->lock);

	stats->num_delivered += skb_queue_len(&rxtid->q);

	while ((skb = skb_dequeue(&rxtid->q)))
		ath6kl_deliver_frames_to_nw_stack(agg_conn->dev, skb);
}