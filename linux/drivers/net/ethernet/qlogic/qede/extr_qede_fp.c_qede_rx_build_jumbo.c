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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct sw_rx_data {int /*<<< orphan*/  data; int /*<<< orphan*/  mapping; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data_len; int /*<<< orphan*/  truesize; } ;
struct qede_rx_queue {scalar_t__ rx_buf_size; scalar_t__ sw_rx_cons; int /*<<< orphan*/  rx_headroom; int /*<<< orphan*/  dev; struct sw_rx_data* sw_rx_ring; } ;
struct qede_dev {int dummy; } ;
struct eth_fast_path_rx_reg_cqe {scalar_t__ bd_num; int /*<<< orphan*/  pkt_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DP_ERR (struct qede_dev*,char*,scalar_t__) ; 
 scalar_t__ NUM_RX_BDS_MAX ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ qede_alloc_rx_buffer (struct qede_rx_queue*,int) ; 
 int /*<<< orphan*/  qede_rx_bd_ring_consume (struct qede_rx_queue*) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static int qede_rx_build_jumbo(struct qede_dev *edev,
			       struct qede_rx_queue *rxq,
			       struct sk_buff *skb,
			       struct eth_fast_path_rx_reg_cqe *cqe,
			       u16 first_bd_len)
{
	u16 pkt_len = le16_to_cpu(cqe->pkt_len);
	struct sw_rx_data *bd;
	u16 bd_cons_idx;
	u8 num_frags;

	pkt_len -= first_bd_len;

	/* We've already used one BD for the SKB. Now take care of the rest */
	for (num_frags = cqe->bd_num - 1; num_frags > 0; num_frags--) {
		u16 cur_size = pkt_len > rxq->rx_buf_size ? rxq->rx_buf_size :
		    pkt_len;

		if (unlikely(!cur_size)) {
			DP_ERR(edev,
			       "Still got %d BDs for mapping jumbo, but length became 0\n",
			       num_frags);
			goto out;
		}

		/* We need a replacement buffer for each BD */
		if (unlikely(qede_alloc_rx_buffer(rxq, true)))
			goto out;

		/* Now that we've allocated the replacement buffer,
		 * we can safely consume the next BD and map it to the SKB.
		 */
		bd_cons_idx = rxq->sw_rx_cons & NUM_RX_BDS_MAX;
		bd = &rxq->sw_rx_ring[bd_cons_idx];
		qede_rx_bd_ring_consume(rxq);

		dma_unmap_page(rxq->dev, bd->mapping,
			       PAGE_SIZE, DMA_FROM_DEVICE);

		skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags++,
				   bd->data, rxq->rx_headroom, cur_size);

		skb->truesize += PAGE_SIZE;
		skb->data_len += cur_size;
		skb->len += cur_size;
		pkt_len -= cur_size;
	}

	if (unlikely(pkt_len))
		DP_ERR(edev,
		       "Mapped all BDs of jumbo, but still have %d bytes\n",
		       pkt_len);

out:
	return num_frags;
}