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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; } ;
struct qede_rx_queue {int /*<<< orphan*/  data_direction; int /*<<< orphan*/  dev; struct qede_agg_info* tpa_info; } ;
struct qede_fastpath {struct qede_rx_queue* rxq; } ;
struct qede_dev {int /*<<< orphan*/  ndev; } ;
struct TYPE_3__ {scalar_t__ page_offset; int /*<<< orphan*/  mapping; } ;
struct qede_agg_info {scalar_t__ state; scalar_t__ frag_id; int tpa_start_fail; struct sk_buff* skb; TYPE_1__ buffer; int /*<<< orphan*/  vlan_tag; } ;
struct eth_fast_path_rx_tpa_end_cqe {size_t tpa_agg_index; scalar_t__ num_of_bds; scalar_t__ num_of_coalesced_segs; scalar_t__ total_packet_len; scalar_t__* len_list; } ;
struct TYPE_4__ {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DP_ERR (struct qede_dev*,char*,...) ; 
 TYPE_2__* NAPI_GRO_CB (struct sk_buff*) ; 
 scalar_t__ PAGE_SIZE ; 
 void* QEDE_AGG_STATE_NONE ; 
 scalar_t__ QEDE_AGG_STATE_START ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  qede_fill_frag_skb (struct qede_dev*,struct qede_rx_queue*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  qede_gro_receive (struct qede_dev*,struct qede_fastpath*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_reuse_page (struct qede_rx_queue*,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int qede_tpa_end(struct qede_dev *edev,
			struct qede_fastpath *fp,
			struct eth_fast_path_rx_tpa_end_cqe *cqe)
{
	struct qede_rx_queue *rxq = fp->rxq;
	struct qede_agg_info *tpa_info;
	struct sk_buff *skb;
	int i;

	tpa_info = &rxq->tpa_info[cqe->tpa_agg_index];
	skb = tpa_info->skb;

	if (tpa_info->buffer.page_offset == PAGE_SIZE)
		dma_unmap_page(rxq->dev, tpa_info->buffer.mapping,
			       PAGE_SIZE, rxq->data_direction);

	for (i = 0; cqe->len_list[i]; i++)
		qede_fill_frag_skb(edev, rxq, cqe->tpa_agg_index,
				   le16_to_cpu(cqe->len_list[i]));
	if (unlikely(i > 1))
		DP_ERR(edev,
		       "Strange - TPA emd with more than a single len_list entry\n");

	if (unlikely(tpa_info->state != QEDE_AGG_STATE_START))
		goto err;

	/* Sanity */
	if (unlikely(cqe->num_of_bds != tpa_info->frag_id + 1))
		DP_ERR(edev,
		       "Strange - TPA had %02x BDs, but SKB has only %d frags\n",
		       cqe->num_of_bds, tpa_info->frag_id);
	if (unlikely(skb->len != le16_to_cpu(cqe->total_packet_len)))
		DP_ERR(edev,
		       "Strange - total packet len [cqe] is %4x but SKB has len %04x\n",
		       le16_to_cpu(cqe->total_packet_len), skb->len);

	/* Finalize the SKB */
	skb->protocol = eth_type_trans(skb, edev->ndev);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	/* tcp_gro_complete() will copy NAPI_GRO_CB(skb)->count
	 * to skb_shinfo(skb)->gso_segs
	 */
	NAPI_GRO_CB(skb)->count = le16_to_cpu(cqe->num_of_coalesced_segs);

	qede_gro_receive(edev, fp, skb, tpa_info->vlan_tag);

	tpa_info->state = QEDE_AGG_STATE_NONE;

	return 1;
err:
	tpa_info->state = QEDE_AGG_STATE_NONE;

	if (tpa_info->tpa_start_fail) {
		qede_reuse_page(rxq, &tpa_info->buffer);
		tpa_info->tpa_start_fail = false;
	}

	dev_kfree_skb_any(tpa_info->skb);
	tpa_info->skb = NULL;
	return 0;
}