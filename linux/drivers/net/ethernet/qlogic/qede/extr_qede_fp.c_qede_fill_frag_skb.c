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
typedef  int /*<<< orphan*/  u16 ;
struct sw_rx_data {int /*<<< orphan*/  data; scalar_t__ page_offset; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; int /*<<< orphan*/  data_len; } ;
struct qede_rx_queue {size_t sw_rx_cons; scalar_t__ rx_buf_seg_size; scalar_t__ rx_headroom; struct qede_agg_info* tpa_info; struct sw_rx_data* sw_rx_ring; } ;
struct qede_dev {int dummy; } ;
struct qede_agg_info {scalar_t__ state; int /*<<< orphan*/  frag_id; struct sk_buff* skb; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NUM_RX_BDS_MAX ; 
 scalar_t__ QEDE_AGG_STATE_ERROR ; 
 scalar_t__ QEDE_AGG_STATE_START ; 
 int /*<<< orphan*/  page_ref_inc (int /*<<< orphan*/ ) ; 
 int qede_realloc_rx_buffer (struct qede_rx_queue*,struct sw_rx_data*) ; 
 int /*<<< orphan*/  qede_recycle_rx_bd_ring (struct qede_rx_queue*,int) ; 
 int /*<<< orphan*/  qede_rx_bd_ring_consume (struct qede_rx_queue*) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int qede_fill_frag_skb(struct qede_dev *edev,
			      struct qede_rx_queue *rxq,
			      u8 tpa_agg_index, u16 len_on_bd)
{
	struct sw_rx_data *current_bd = &rxq->sw_rx_ring[rxq->sw_rx_cons &
							 NUM_RX_BDS_MAX];
	struct qede_agg_info *tpa_info = &rxq->tpa_info[tpa_agg_index];
	struct sk_buff *skb = tpa_info->skb;

	if (unlikely(tpa_info->state != QEDE_AGG_STATE_START))
		goto out;

	/* Add one frag and update the appropriate fields in the skb */
	skb_fill_page_desc(skb, tpa_info->frag_id++,
			   current_bd->data,
			   current_bd->page_offset + rxq->rx_headroom,
			   len_on_bd);

	if (unlikely(qede_realloc_rx_buffer(rxq, current_bd))) {
		/* Incr page ref count to reuse on allocation failure
		 * so that it doesn't get freed while freeing SKB.
		 */
		page_ref_inc(current_bd->data);
		goto out;
	}

	qede_rx_bd_ring_consume(rxq);

	skb->data_len += len_on_bd;
	skb->truesize += rxq->rx_buf_seg_size;
	skb->len += len_on_bd;

	return 0;

out:
	tpa_info->state = QEDE_AGG_STATE_ERROR;
	qede_recycle_rx_bd_ring(rxq, 1);

	return -ENOMEM;
}