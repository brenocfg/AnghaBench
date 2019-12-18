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
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  data; } ;
struct lan743x_tx {int ring_size; int ts_flags; int /*<<< orphan*/  ring_lock; TYPE_2__* adapter; struct sk_buff* overflow_skb; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; } ;
struct TYPE_3__ {int tx_flags; int nr_frags; int /*<<< orphan*/ * frags; int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int SKBTX_HW_TSTAMP ; 
 int SKBTX_IN_PROGRESS ; 
 int TX_TS_FLAG_ONE_STEP_SYNC ; 
 int TX_TS_FLAG_TIMESTAMPING_ENABLED ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ lan743x_ptp_request_tx_timestamp (TYPE_2__*) ; 
 scalar_t__ lan743x_tx_frame_add_fragment (struct lan743x_tx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  lan743x_tx_frame_add_lso (struct lan743x_tx*,unsigned int,int) ; 
 int /*<<< orphan*/  lan743x_tx_frame_end (struct lan743x_tx*,struct sk_buff*,int,int) ; 
 scalar_t__ lan743x_tx_frame_start (struct lan743x_tx*,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int) ; 
 int lan743x_tx_get_avail_desc (struct lan743x_tx*) ; 
 int lan743x_tx_get_desc_cnt (struct lan743x_tx*,struct sk_buff*) ; 
 unsigned int max (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 int skb_is_gso (struct sk_buff*) ; 
 unsigned int skb_pagelen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t lan743x_tx_xmit_frame(struct lan743x_tx *tx,
					 struct sk_buff *skb)
{
	int required_number_of_descriptors = 0;
	unsigned int start_frame_length = 0;
	unsigned int frame_length = 0;
	unsigned int head_length = 0;
	unsigned long irq_flags = 0;
	bool do_timestamp = false;
	bool ignore_sync = false;
	int nr_frags = 0;
	bool gso = false;
	int j;

	required_number_of_descriptors = lan743x_tx_get_desc_cnt(tx, skb);

	spin_lock_irqsave(&tx->ring_lock, irq_flags);
	if (required_number_of_descriptors >
		lan743x_tx_get_avail_desc(tx)) {
		if (required_number_of_descriptors > (tx->ring_size - 1)) {
			dev_kfree_skb(skb);
		} else {
			/* save to overflow buffer */
			tx->overflow_skb = skb;
			netif_stop_queue(tx->adapter->netdev);
		}
		goto unlock;
	}

	/* space available, transmit skb  */
	if ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
	    (tx->ts_flags & TX_TS_FLAG_TIMESTAMPING_ENABLED) &&
	    (lan743x_ptp_request_tx_timestamp(tx->adapter))) {
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		do_timestamp = true;
		if (tx->ts_flags & TX_TS_FLAG_ONE_STEP_SYNC)
			ignore_sync = true;
	}
	head_length = skb_headlen(skb);
	frame_length = skb_pagelen(skb);
	nr_frags = skb_shinfo(skb)->nr_frags;
	start_frame_length = frame_length;
	gso = skb_is_gso(skb);
	if (gso) {
		start_frame_length = max(skb_shinfo(skb)->gso_size,
					 (unsigned short)8);
	}

	if (lan743x_tx_frame_start(tx,
				   skb->data, head_length,
				   start_frame_length,
				   do_timestamp,
				   skb->ip_summed == CHECKSUM_PARTIAL)) {
		dev_kfree_skb(skb);
		goto unlock;
	}

	if (gso)
		lan743x_tx_frame_add_lso(tx, frame_length, nr_frags);

	if (nr_frags <= 0)
		goto finish;

	for (j = 0; j < nr_frags; j++) {
		const skb_frag_t *frag = &(skb_shinfo(skb)->frags[j]);

		if (lan743x_tx_frame_add_fragment(tx, frag, frame_length)) {
			/* upon error no need to call
			 *	lan743x_tx_frame_end
			 * frame assembler clean up was performed inside
			 *	lan743x_tx_frame_add_fragment
			 */
			dev_kfree_skb(skb);
			goto unlock;
		}
	}

finish:
	lan743x_tx_frame_end(tx, skb, do_timestamp, ignore_sync);

unlock:
	spin_unlock_irqrestore(&tx->ring_lock, irq_flags);
	return NETDEV_TX_OK;
}