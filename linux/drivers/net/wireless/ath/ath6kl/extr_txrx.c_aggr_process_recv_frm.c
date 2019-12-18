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
typedef  int u16 ;
struct skb_hold_q {int is_amsdu; int seq_no; struct sk_buff* skb; } ;
struct sk_buff {int dummy; } ;
struct rxtid_stats {int /*<<< orphan*/  num_mpdu; int /*<<< orphan*/  num_amsdu; int /*<<< orphan*/  num_dups; int /*<<< orphan*/  num_oow; int /*<<< orphan*/  num_into_aggr; } ;
struct rxtid {int seq_next; int hold_q_sz; int timer_mon; int /*<<< orphan*/  lock; struct skb_hold_q* hold_q; int /*<<< orphan*/  q; int /*<<< orphan*/  aggr; } ;
struct aggr_info_conn {int timer_scheduled; int /*<<< orphan*/  timer; int /*<<< orphan*/  dev; int /*<<< orphan*/  aggr_info; struct rxtid_stats* stat; struct rxtid* rx_tid; } ;

/* Variables and functions */
 int AGGR_RX_TIMEOUT ; 
 int AGGR_WIN_IDX (int,int) ; 
 int ATH6KL_MAX_SEQ_NO ; 
 int HZ ; 
 int /*<<< orphan*/  aggr_deque_frms (struct aggr_info_conn*,size_t,int,int) ; 
 int /*<<< orphan*/  aggr_slice_amsdu (int /*<<< orphan*/ ,struct rxtid*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath6kl_deliver_frames_to_nw_stack (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool aggr_process_recv_frm(struct aggr_info_conn *agg_conn, u8 tid,
				  u16 seq_no,
				  bool is_amsdu, struct sk_buff *frame)
{
	struct rxtid *rxtid;
	struct rxtid_stats *stats;
	struct sk_buff *skb;
	struct skb_hold_q *node;
	u16 idx, st, cur, end;
	bool is_queued = false;
	u16 extended_end;

	rxtid = &agg_conn->rx_tid[tid];
	stats = &agg_conn->stat[tid];

	stats->num_into_aggr++;

	if (!rxtid->aggr) {
		if (is_amsdu) {
			aggr_slice_amsdu(agg_conn->aggr_info, rxtid, frame);
			is_queued = true;
			stats->num_amsdu++;
			while ((skb = skb_dequeue(&rxtid->q)))
				ath6kl_deliver_frames_to_nw_stack(agg_conn->dev,
								  skb);
		}
		return is_queued;
	}

	/* Check the incoming sequence no, if it's in the window */
	st = rxtid->seq_next;
	cur = seq_no;
	end = (st + rxtid->hold_q_sz-1) & ATH6KL_MAX_SEQ_NO;

	if (((st < end) && (cur < st || cur > end)) ||
	    ((st > end) && (cur > end) && (cur < st))) {
		extended_end = (end + rxtid->hold_q_sz - 1) &
			ATH6KL_MAX_SEQ_NO;

		if (((end < extended_end) &&
		     (cur < end || cur > extended_end)) ||
		    ((end > extended_end) && (cur > extended_end) &&
		     (cur < end))) {
			aggr_deque_frms(agg_conn, tid, 0, 0);
			spin_lock_bh(&rxtid->lock);
			if (cur >= rxtid->hold_q_sz - 1)
				rxtid->seq_next = cur - (rxtid->hold_q_sz - 1);
			else
				rxtid->seq_next = ATH6KL_MAX_SEQ_NO -
						  (rxtid->hold_q_sz - 2 - cur);
			spin_unlock_bh(&rxtid->lock);
		} else {
			/*
			 * Dequeue only those frames that are outside the
			 * new shifted window.
			 */
			if (cur >= rxtid->hold_q_sz - 1)
				st = cur - (rxtid->hold_q_sz - 1);
			else
				st = ATH6KL_MAX_SEQ_NO -
					(rxtid->hold_q_sz - 2 - cur);

			aggr_deque_frms(agg_conn, tid, st, 0);
		}

		stats->num_oow++;
	}

	idx = AGGR_WIN_IDX(seq_no, rxtid->hold_q_sz);

	node = &rxtid->hold_q[idx];

	spin_lock_bh(&rxtid->lock);

	/*
	 * Is the cur frame duplicate or something beyond our window(hold_q
	 * -> which is 2x, already)?
	 *
	 * 1. Duplicate is easy - drop incoming frame.
	 * 2. Not falling in current sliding window.
	 *  2a. is the frame_seq_no preceding current tid_seq_no?
	 *      -> drop the frame. perhaps sender did not get our ACK.
	 *         this is taken care of above.
	 *  2b. is the frame_seq_no beyond window(st, TID_WINDOW_SZ);
	 *      -> Taken care of it above, by moving window forward.
	 */
	dev_kfree_skb(node->skb);
	stats->num_dups++;

	node->skb = frame;
	is_queued = true;
	node->is_amsdu = is_amsdu;
	node->seq_no = seq_no;

	if (node->is_amsdu)
		stats->num_amsdu++;
	else
		stats->num_mpdu++;

	spin_unlock_bh(&rxtid->lock);

	aggr_deque_frms(agg_conn, tid, 0, 1);

	if (agg_conn->timer_scheduled)
		return is_queued;

	spin_lock_bh(&rxtid->lock);
	for (idx = 0; idx < rxtid->hold_q_sz; idx++) {
		if (rxtid->hold_q[idx].skb) {
			/*
			 * There is a frame in the queue and no
			 * timer so start a timer to ensure that
			 * the frame doesn't remain stuck
			 * forever.
			 */
			agg_conn->timer_scheduled = true;
			mod_timer(&agg_conn->timer,
				  (jiffies + (HZ * AGGR_RX_TIMEOUT) / 1000));
			rxtid->timer_mon = true;
			break;
		}
	}
	spin_unlock_bh(&rxtid->lock);

	return is_queued;
}